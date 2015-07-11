//
// Created by Nathan on 7/10/2015.
//

#include "IsometricBoardVisualizer.h"

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

    sf::Vector2f tl = transform.transformPoint(0, 0),
            tr = transform.transformPoint(width - 1, 0),
            br = transform.transformPoint(width - 1, height - 1),
            bl = transform.transformPoint(0, height - 1);

    int maxX = std::max(std::max(tl.x, tr.x), std::max(br.x, bl.x));
    int maxY = std::max(std::max(tl.y, tr.y), std::max(br.y, bl.y));
    int minX = std::min(std::min(tl.x, tr.x), std::min(br.x, bl.x));
    int minY = std::min(std::min(tl.x, tr.x), std::min(br.x, bl.x));

    viewport.top = minY;
    viewport.left = minX;
    viewport.width = maxX - minX;
    viewport.height = maxY - minY;



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
    sf::VertexArray linesVert(sf::Lines, (width + 1) * 2);
    for (int u = 0; u <= width; u++)
    {
        linesVert[2 * u].position = transform.transformPoint(u, 0);
        linesVert[2 * u + 1].position = transform.transformPoint(u, height);

        linesVert[2 * u].color = sf::Color::Black;
        linesVert[2 * u + 1].color = sf::Color::Black;
    }



    sf::VertexArray linesHorz(sf::Lines, (height + 1) * 2);
    for (int v = 0; v <= height; v++)
    {
        linesHorz[2 * v].position = transform.transformPoint(0, v);
        linesHorz[2 * v + 1].position = transform.transformPoint(width, v);

        linesHorz[2 * v].color = sf::Color::Black;
        linesHorz[2 * v + 1].color = sf::Color::Black;
    }

    target->draw(linesVert);
    target->draw(linesHorz);
}
