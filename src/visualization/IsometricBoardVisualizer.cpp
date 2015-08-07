//
// Created by Nathan on 7/10/2015.
//

#include "visualization/IsometricBoardVisualizer.h"

namespace undocked {
    namespace visualization {
        using world::CellularBoard;
        using world::BoardCell;

        IsometricBoardVisualizer::IsometricBoardVisualizer(sf::Vector2f uBasis, sf::Vector2f vBasis) :
        width(0),
        height(0),
        target(),
        Sux(uBasis.x, vBasis.x, 0,
            uBasis.y, vBasis.y, 0,
            0,        0,        1) {
        }

        void IsometricBoardVisualizer::update(CellularBoard* board) {
            // get the width and height in (u,v) of the board
            int width = board->getWidth(), height = board->getHeight();

            // if the size of the board has changed, we need to expand or shrink the buffer
            if (width != this->width || height != this->height) {
                this->width = width;
                this->height = height;

                std::vector<sf::Vector2f> corners = {{0, 0}, {width, 0}, {0, height}, {width, height}};
                std::transform(corners.begin(), corners.end(), corners.begin(), [this](sf::Vector2f v) {
                    return Sux.transformPoint(v);
                });

                auto minX = std::min_element(corners.begin(), corners.end(), [](sf::Vector2f v1, sf::Vector2f v2) {
                    return v1.x < v2.x;
                });

                auto minY = std::min_element(corners.begin(), corners.end(), [](sf::Vector2f v1, sf::Vector2f v2) {
                    return v1.y < v2.y;
                });

                auto maxX = std::max_element(corners.begin(), corners.end(), [](sf::Vector2f v1, sf::Vector2f v2) {
                    return v1.x < v2.x;
                });

                auto maxY = std::max_element(corners.begin(), corners.end(), [](sf::Vector2f v1, sf::Vector2f v2) {
                    return v1.y < v2.y;
                });

                uint32_t xDistance = (uint32_t)std::ceil((*maxX).x - (*minX).x);
                uint32_t yDistance = (uint32_t)std::ceil((*maxY).y - (*minY).y);
                target.create(xDistance, yDistance);
                offset.x = (*minX).x;
                offset.y = (*minY).y;
                sf::View view(sf::Vector2f((*minX).x + xDistance / 2, 0), sf::Vector2f(xDistance, yDistance));
                target.setView(view);
            }

            // clear the previous board in the buffer (do we need to do this?)
            target.clear(sf::Color::Transparent);

            // default identity transform
            Transform transform;

            // compose the isometric perspective transform
            transform = transform * Sux;

            for (int v = 0; v < height; v++) {
                for (int u = 0; u < width; u++) {
                    BoardCell cell = board->getCell(u, v);

                    sf::VertexArray quad(sf::Quads, 4);

                    quad[0].position = transform.transformPoint(sf::Vector2f(u, v));
                    quad[1].position = transform.transformPoint(sf::Vector2f(u + 1, v));
                    quad[2].position = transform.transformPoint(sf::Vector2f(u + 1, v + 1));
                    quad[3].position = transform.transformPoint(sf::Vector2f(u, v + 1));

                    quad[0].color = cell.getBaseColor();
                    quad[1].color = cell.getBaseColor();
                    quad[2].color = cell.getBaseColor();
                    quad[3].color = cell.getBaseColor();

                    target.draw(quad);
                }
            }

            target.display();
        }

        void IsometricBoardVisualizer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            sf::Sprite sprite;
            sprite.setTexture(this->target.getTexture());
            sprite.setPosition(this->offset);
            target.draw(sprite);
        }
    }
}