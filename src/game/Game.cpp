//
// Created by Nathan on 7/10/2015.
//
#include "game/Game.h"

#include "event/EventManager.h"
#include "event/ClickAtCoordinate.h"
#include "game/generation/ClusterSeederV2.h"

namespace undocked {
    namespace game {
        using generation::ClusterSeederV2;
        using visualization::IsometricSceneVisualizer;
        using event::EventManager;
        using event::ClickAtCoordinate;

        GameAction generatePathingAction( sf::Vector2i end, Unit* unit, GameState* inState, int speed = 1) {
            sf::Vector2i location = unit->getLocation();
            std::vector<sf::Vector2i> path = inState->getBoard()->calculatePath(location, end);
            uint32_t i = 0;
            auto tickAction = [=] (GameState* state) mutable {
                if (i < path.size())
                    unit->setLocation(path[i]);

                return ++i < path.size();
            };

            GameAction action(tickAction);

            return action;
        }

        bool Game::run() {
            target.clear(sf::Color::Transparent);
            uiTarget.clear(sf::Color::Transparent);
            state->tick();

            visualizer.update(state);

            target.draw(boardVisualizer);
            target.draw(visualizer);
            uiTarget.draw(uiManager);
            target.display();
            uiTarget.display();
            return false;
        }

        Game::Game(uint32_t width, uint32_t height) :
                uiManager(width, height),
                visualizer(sf::Vector2f(20, -10), sf::Vector2f(20, 10)),
                boardVisualizer(sf::Vector2f(20, -10), sf::Vector2f(20, 10)) {

            target.create(width, height);
            target.clear(sf::Color::Red);
            uiTarget.create(width, height);
            uiTarget.clear(sf::Color::Transparent);

            ClusterSeederV2 seeder = ClusterSeederV2();

            box = (ui::MessageBox*) uiManager.createMessageBox(0, -149, 400, 150, "Select a Unit");
            auto f2 = ui::UiElement::anchorPoints["BOTTOM_LEFT"];
            box->setAnchorPoint(f2);

            gameView = sf::View(sf::Vector2f(1888, -100), sf::Vector2f(width, height));
            gameView.zoom(2.5);

            state = new GameState(75, 75, seeder);

            boardVisualizer.update(state->getBoard());
            auto f = std::bind(&Game::nativeEventHandler, this, std::placeholders::_1);
            EventManager::getInstance()->addListener(f);
        }

        void Game::nativeEventHandler(sf::Event event) {
            // TODO: all this game event logic should be factored out into another, subtyped, class
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mapCoordinates = target.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                visualizer.setInputPosition(mapCoordinates);

                if (middleButtonDown) {
                    int deltaX = (int)std::round((event.mouseMove.x - mouseStart.x) * gameView.getSize().x / target.getSize().x);
                    int deltaY = (int)std::round((event.mouseMove.y - mouseStart.y) * gameView.getSize().y / target.getSize().y);
                    gameView.setCenter(mapStart.x - deltaX, mapStart.y - deltaY);
                    target.setView(gameView);
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    mouseStart.x = event.mouseButton.x;
                    mouseStart.y = event.mouseButton.y;

                    mapStart.x = (int)gameView.getCenter().x;
                    mapStart.y = (int)gameView.getCenter().y;

                    middleButtonDown = true;
                } else if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    auto location = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                    // transforms the screen coordinates of the mouse to the appropriate pixels on the map
                    sf::Vector2f mapCoordinates = target.mapPixelToCoords(location);

                    Unit* focusedUnit = visualizer.findUnitAtLocation(mapCoordinates);
                    state->selectUnit(focusedUnit);

                    if (focusedUnit) {
                        std::stringstream stringstream;
                        stringstream << "Selected Unit at: (" << focusedUnit->getLocation().x
                        << ", " << focusedUnit->getLocation().y << ")" << std::endl;
                        stringstream << "Health: " << focusedUnit->getHealth() << std::endl;
                        stringstream << "Age: " << focusedUnit->getAge() << std::endl;
                        stringstream << "Death Chance: " << focusedUnit->deathChance() << std::endl;
                        box->setMessage(stringstream.str());
                    } else {
                        box->setMessage("Select a Unit");
                    }

                    // transform the map pixel coordinates to the (u,v) map coordinates
                    sf::Transform transform = visualizer.getTransform().getInverse();
                    sf::Vector2f point = transform.transformPoint(mapCoordinates);

                    EventManager::getInstance()->pushEvent(ClickAtCoordinate(point));
                } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    auto location = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                    sf::Vector2f mapCoordinates = target.mapPixelToCoords(location);

                    if (state->selectedUnit) {
                        sf::Transform transform = visualizer.getTransform().getInverse();
                        sf::Vector2f point = transform.transformPoint(mapCoordinates);

                        // only queue an action if the mouse was pressed within the board
                        if (point.x >= 0 && point.y >= 0 &&
                            point.x < state->getBoard()->getWidth() &&
                            point.y < state->getBoard()->getHeight()) {

                            sf::Vector2i destination((int)point.x, (int)point.y);
                            GameAction action = generatePathingAction(destination, state->selectedUnit, state);

                            if (event.key.shift) {
                                state->queueAction(action, state->selectedUnit);
                            } else {
                                state->putAction(action, state->selectedUnit);
                            }
                        }
                    }
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    middleButtonDown = false;
                }
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) gameView.zoom(0.75);
                else if (event.mouseWheelScroll.delta < 0) gameView.zoom(1 / 0.75f);

                target.setView(gameView);
            } else if (event.type == sf::Event::Resized) {
                target.create(event.size.width, event.size.height);
                uiTarget.create(event.size.width, event.size.height);
                uiManager.updateSize(event.size.width, event.size.height);

                sf::Vector2u size = target.getSize();
                gameView = sf::View(gameView.getCenter(), sf::Vector2f(size.x, size.y));
                target.setView(gameView);
            }
        }

        void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            sf::Sprite sprite;
            sprite.setTexture(this->target.getTexture());
            target.draw(sprite);
            sprite.setTexture(uiTarget.getTexture());
            target.draw(sprite);
        }
    }
}
