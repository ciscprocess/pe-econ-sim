//
// Created by Nathan on 7/10/2015.
//

#include <ClusterSeederV1.h>
#include "Game.h"

#include <EventManager.h>
#include <ClickAtCoordinate.h>

using sf::Vector3f;

GameAction generatePathingAction( sf::Vector2i end, Unit* unit, int speed = 1) {

    auto tickAction = [=] (GameState* state) mutable {
        sf::Vector2i location = unit->getLocation();
        sf::Vector2i displacement = end - location;
        if (std::abs(displacement.x) > 0 && std::abs(displacement.y) > 0) {
            int choice = rand() % 2;
            if (choice == 0) {
                int delta = displacement.x > 0 ? 1 : -1;
                location.x = location.x + delta;
                unit->setLocation(location);
            } else {
                int delta = displacement.y > 0 ? 1 : -1;
                location.y = location.y + delta;
                unit->setLocation(location);
            }
        } else if (std::abs(displacement.x) > 0) {
            int delta = displacement.x > 0 ? 1 : -1;
            location.x = location.x + delta;
            unit->setLocation(location);
        } else if (std::abs(displacement.y) > 0) {
            int delta = displacement.y > 0 ? 1 : -1;
            location.y = location.y + delta;
            unit->setLocation(location);
        }

        return std::abs(displacement.x) > 0 || std::abs(displacement.y) > 0;
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
    ClusterSeederV1 seeder = ClusterSeederV1();

    gameView = sf::View(sf::Vector2f(1888, -100), sf::Vector2f(1024, 768));
    gameView.zoom(3.5);
    target->setView(gameView);

    state = new GameState(100, 100, seeder);
    visualizer = new IsometricSceneVisualizer(Vector3f(20, -10, 1), Vector3f(20, 10, 1), target);

    auto f = std::bind(&Game::nativeEventHandler, this, std::placeholders::_1);
    EventManager::getInstance()->addListener(f);
}

void Game::nativeEventHandler(sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mapCoords = target->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        visualizer->setInputPosition(mapCoords);

        if (middleButtonDown) {
            // TODO: factor out window dimensions
            int deltaX = (int)std::round((event.mouseMove.x - mouseStart.x) * gameView.getSize().x / 1024.0);
            int deltaY = (int)std::round((event.mouseMove.y - mouseStart.y) * gameView.getSize().x / 768.0);
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
            sf::Vector2f mapCoords = target->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            bool found = false;
            for (int i = 0; i < visualizer->sprites.size(); i++) {
                sf::Sprite sprite = visualizer->sprites[i].first;
                if (sprite.getGlobalBounds().contains(mapCoords)) {
                    Unit* unit = visualizer->sprites[i].second;
                    state->selectUnit(unit);
                    found = true;
                    break;
                }
            }

            if (!found) {
                state->selectedUnit = nullptr;
            }

            sf::Transform transform = visualizer->getTransform().getInverse();
            sf::Vector2f point = transform.transformPoint(mapCoords);
            EventManager::getInstance()->pushEvent(ClickAtCoordinate(point));
        } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
            sf::Vector2f mapCoords = target->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            if (state->selectedUnit) {
                sf::Transform transform = visualizer->getTransform().getInverse();
                sf::Vector2f point = transform.transformPoint(mapCoords);
                GameAction action = generatePathingAction(sf::Vector2i((int)point.x, (int)point.y), state->selectedUnit);
                state->queueAction(action, state->selectedUnit);
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Middle) {
            middleButtonDown = false;
        }
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) gameView.zoom(0.9);
        else if (event.mouseWheelScroll.delta < 0) gameView.zoom(1/0.9);
    }
}

void Game::interactionEventHandler(GameInteractionEvent event) {

}
