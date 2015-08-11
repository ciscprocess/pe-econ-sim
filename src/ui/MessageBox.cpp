//
// Created by Nathan on 8/1/2015.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "ui/MessageBox.h"

namespace undocked {
    namespace ui {
        void MessageBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            sf::RectangleShape shape(sf::Vector2f(area.width, area.height));
            sf::Vector2i position = sf::Vector2i(area.left, area.top) + anchorPoint(this);
            shape.setPosition(position.x, position.y);

            shape.setFillColor(sf::Color(65, 65, 65));

            sf::Font font;
            if (!font.loadFromFile("data/cour.ttf")) {

            }

            sf::Text text;
            text.setFont(font);
            text.setString(message);
            text.setCharacterSize(12);
            text.setColor(sf::Color::White);
            text.setPosition(position.x + 10, position.y + 10);

            target.draw(shape);
            target.draw(text);
        }
    }
}