//
// Created by Nathan on 7/10/2015.
//

#include <numeric/Random.h>
#include "visualization/IsometricSceneVisualizer.h"
namespace undocked {
    namespace visualization {
        IsometricSceneVisualizer::IsometricSceneVisualizer(sf::Vector2f uBasis, sf::Vector2f vBasis) :
                Sux(uBasis.x, vBasis.x, 0,
                    uBasis.y, vBasis.y, 0,
                    0,        0,        1) {
            Sxu = Sux.getInverse();
        }

        void IsometricSceneVisualizer::update(GameState *state) {
            sprites.clear();
            this->state = state;
            for (int i = 0; i < state->units.size(); i++) {
                Unit* unit = state->units[i];
                sf::Texture* texture = unit->getTexture();

                // TODO: potential speed problem: the texture is copied in memory every frame
                sf::Sprite sprite;
                sprite.setTexture(*texture);
                sf::Vector2f gamePoint(unit->getLocation().x, unit->getLocation().y);
                gamePoint = gamePoint + unit->getOffset();
                sf::Vector2f screenPoint = Sux.transformPoint(gamePoint);
                sprite.setPosition(screenPoint);

                sprites.push_back(std::make_pair(sprite, unit));
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

        numeric::Random rando;
        void IsometricSceneVisualizer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            if (inputEnabled) {
                auto tp = Sxu.transformPoint(inputPosition);
                int u = (int)std::floor(tp.x), v = (int)std::floor(tp.y);

                sf::VertexArray quad(sf::Quads, 4);

                quad[0].position = Sux.transformPoint(sf::Vector2f(u, v));
                quad[1].position = Sux.transformPoint(sf::Vector2f(u + 1, v));
                quad[2].position = Sux.transformPoint(sf::Vector2f(u + 1, v + 1));
                quad[3].position = Sux.transformPoint(sf::Vector2f(u, v + 1));

                quad[0].color = sf::Color::Cyan;
                quad[1].color = sf::Color::Cyan;
                quad[2].color = sf::Color::Cyan;
                quad[3].color = sf::Color::Cyan;

                target.draw(quad);
            }

            for (int i = 0; i < sprites.size(); i++) {
                auto pair = sprites[i];
                auto sprite = pair.first;
                auto unit = pair.second;

                // draw the selection ellipse beneath the character
                if (pair.second == state->selectedUnit) {
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
                    target.draw(transformedEllipse);
                }

                target.draw(sprite);
            }
        }
    }
}
