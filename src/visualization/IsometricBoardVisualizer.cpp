//
// Created by Nathan on 7/10/2015.
//

#include "visualization/IsometricBoardVisualizer.h"

namespace undocked {
    namespace visualization {
        using world::CellularBoard;
        using world::BoardCell;

        IsometricBoardVisualizer::IsometricBoardVisualizer(Transform& sux, sf::RenderTarget* target) {
            Sux = sux;
            this->target = target;
        }

        void IsometricBoardVisualizer::draw(CellularBoard* board, sf::Vector2f* input) {
            // default identity transform
            Transform transform;

            // compose the isometric perspective transform
            transform = transform * Sux;

            // get the width and height in (u,v) of the board
            int width = board->getWidth(), height = board->getHeight();

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

                    target->draw(quad);
                }
            }

            if (input) {
                Transform inv = transform.getInverse();
                auto tp = inv.transformPoint(*input);
                int u = (int)std::floor(tp.x), v = (int)std::floor(tp.y);

                sf::VertexArray quad(sf::Quads, 4);

                quad[0].position = transform.transformPoint(sf::Vector2f(u, v));
                quad[1].position = transform.transformPoint(sf::Vector2f(u + 1, v));
                quad[2].position = transform.transformPoint(sf::Vector2f(u + 1, v + 1));
                quad[3].position = transform.transformPoint(sf::Vector2f(u, v + 1));

                quad[0].color = sf::Color::Cyan;
                quad[1].color = sf::Color::Cyan;
                quad[2].color = sf::Color::Cyan;
                quad[3].color = sf::Color::Cyan;

                target->draw(quad);
            }


            // draw the lines
            sf::VertexArray linesVertical(sf::Lines, (width + 1) * 2);
            for (int u = 0; u <= width; u++) {
                linesVertical[2 * u].position = transform.transformPoint(u, 0);
                linesVertical[2 * u + 1].position = transform.transformPoint(u, height);

                linesVertical[2 * u].color = sf::Color::Black;
                linesVertical[2 * u + 1].color = sf::Color::Black;
            }



            sf::VertexArray linesHorizontal(sf::Lines, (height + 1) * 2);
            for (int v = 0; v <= height; v++) {
                linesHorizontal[2 * v].position = transform.transformPoint(0, v);
                linesHorizontal[2 * v + 1].position = transform.transformPoint(width, v);

                linesHorizontal[2 * v].color = sf::Color::Black;
                linesHorizontal[2 * v + 1].color = sf::Color::Black;
            }

            target->draw(linesVertical);
            target->draw(linesHorizontal);
        }

    }
}