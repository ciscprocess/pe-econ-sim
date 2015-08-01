//
// Created by Nathan on 7/10/2015.
//
#include "game/Game.h"

#include "event/EventManager.h"
#include "event/ClickAtCoordinate.h"
#include "game/generation/ClusterSeederV2.h"


GameAction generatePathingAction( sf::Vector2i end, Unit* unit, int speed = 1) {

    auto tickAction = [=] (GameState* state) mutable {
        sf::Vector2i location = unit->getLocation();
        std::vector<sf::Vector2i> path = state->getBoard()->calculatePath(unit->getLocation(), end);

        if (path.size() > 0)
            unit->setLocation(path[0]);

        return path.size() > 0;
    };

    GameAction action(tickAction);

    return action;
}

bool Game::run() {
    state->tick();
    visualizer->draw(state);
    target->setView(gameView);
    return false;
}

Game::Game(sf::RenderTarget* target) : target(target) {
    ClusterSeederV2 seeder = ClusterSeederV2();

    gameView = sf::View(sf::Vector2f(1888, -100), sf::Vector2f(1024, 768));
    gameView.zoom(3.5);
    target->setView(gameView);

    state = new GameState(100, 100, seeder);
    visualizer = new IsometricSceneVisualizer(sf::Vector2f(20, -10), sf::Vector2f(20, 10), target);

    auto f = std::bind(&Game::nativeEventHandler, this, std::placeholders::_1);
    EventManager::getInstance()->addListener(f);
}

void Game::nativeEventHandler(sf::Event event) {
    // TODO: all this game event logic should be factored out into another, subtyped, class
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mapCoordinates = target->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        visualizer->setInputPosition(mapCoordinates);

        if (middleButtonDown) {
            int deltaX = (int)std::round((event.mouseMove.x - mouseStart.x) * gameView.getSize().x / target->getSize().x);
            int deltaY = (int)std::round((event.mouseMove.y - mouseStart.y) * gameView.getSize().y / target->getSize().y);
            gameView.setCenter(mapStart.x - deltaX, mapStart.y - deltaY);
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
            sf::Vector2f mapCoordinates = target->mapPixelToCoords(location);

            Unit* focusedUnit = visualizer->findUnitAtLocation(mapCoordinates);
            state->selectUnit(focusedUnit);

            // transform the map pixel coordinates to the (u,v) map coordinates
            sf::Transform transform = visualizer->getTransform().getInverse();
            sf::Vector2f point = transform.transformPoint(mapCoordinates);

            EventManager::getInstance()->pushEvent(ClickAtCoordinate(point));
        } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
            auto location = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            sf::Vector2f mapCoordinates = target->mapPixelToCoords(location);

            if (state->selectedUnit) {
                sf::Transform transform = visualizer->getTransform().getInverse();
                sf::Vector2f point = transform.transformPoint(mapCoordinates);

                // only queue an action if the mouse was pressed within the board
                if (point.x >= 0 && point.y >= 0 &&
                    point.x < state->getBoard()->getWidth() &&
                    point.y < state->getBoard()->getHeight()) {

                    auto destination = sf::Vector2i((int)point.x, (int)point.y);
                    GameAction action = generatePathingAction(destination, state->selectedUnit);

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
        if (event.mouseWheelScroll.delta > 0) gameView.zoom(0.9);
        else if (event.mouseWheelScroll.delta < 0) gameView.zoom(1 / 0.9f);
    } else if (event.type == sf::Event::Resized) {
        sf::Vector2u size = target->getSize();
        gameView = sf::View(gameView.getCenter(), sf::Vector2f(size.x, size.y));
    }
}
