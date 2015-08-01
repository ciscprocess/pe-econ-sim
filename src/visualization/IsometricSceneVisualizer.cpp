//
// Created by Nathan on 7/10/2015.
//

#include "visualization/IsometricSceneVisualizer.h"
namespace undocked {
    namespace visualization {
        IsometricSceneVisualizer::IsometricSceneVisualizer(sf::Vector2f uBasis, sf::Vector2f vBasis, sf::RenderTarget* target) :
                Sux(uBasis.x, vBasis.x, 0,
                    uBasis.y, vBasis.y, 0,
                    0,        0,        1),
                boardVisualizer(Sux, target),
                target(target) {
            this->uBasis = uBasis;
            this->vBasis = vBasis;
        }

        void IsometricSceneVisualizer::draw(GameState *state) {
            boardVisualizer.draw(state->getBoard(), inputEnabled ? &inputPosition : nullptr);

            sprites.clear();

            for (int i = 0; i < state->units.size(); i++) {
                Unit* unit = state->units[i];
                sf::Texture* texture = unit->getTexture();

                // TODO: potential speed problem: the texture is copied in memory every frame
                sf::Sprite sprite;
                sprite.setTexture(*texture);
                sf::Vector2f gamePoint = sf::Vector2f(unit->getLocation().x, unit->getLocation().y);
                gamePoint = gamePoint + unit->getOffset();
                sf::Vector2f screenPoint = Sux.transformPoint(gamePoint);
                sprite.setPosition(screenPoint);


                // draw the selection ellipse beneath the character
                if (unit == state->selectedUnit) {
                    sf::ConvexShape transformedEllipse;
                    transformedEllipse.setPointCount(25);
                    for (int i = 0; i < 25; i++) {
                        double t = (i / 25.0) * 2 * 3.14159;
                        double u = (std::sin(t) / 2);
                        double v = (std::cos(t) / 2);
                        sf::Vector2f tp = Sux.transformPoint(u, v);
                        transformedEllipse.setPoint(i, tp);
                    }
                    transformedEllipse.setFillColor(sf::Color::Transparent);
                    transformedEllipse.setOutlineColor(sf::Color::White);
                    transformedEllipse.setOutlineThickness(1);
                    sf::Vector2f gamePoint2 = sf::Vector2f(unit->getLocation().x, unit->getLocation().y)
                                              + sf::Vector2f(0.5, 0.5);

                    sf::Vector2f screenPoint2 = Sux.transformPoint(gamePoint2);

                    transformedEllipse.setPosition(screenPoint2);
                    target->draw(transformedEllipse);
                }

                sprites.push_back(std::make_pair(sprite, unit));
                target->draw(sprite);
            }
        }

        Unit *IsometricSceneVisualizer::findUnitAtLocation(sf::Vector2f location) {
            Unit* found = nullptr;

            for (int i = 0; i < this->sprites.size(); i++) {
                sf::Sprite sprite = this->sprites[i].first;
                if (sprite.getGlobalBounds().contains(location)) {
                    found = this->sprites[i].second;
                    break;
                }
            }

            return found;
        }
    }
}
