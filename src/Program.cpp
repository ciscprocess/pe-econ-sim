//
// Created by Nathan on 7/10/2015.
//

#include "Program.h"

bool Program::run(int tick) {
    if (tick != 0) return true;
    buffer->clear(sf::Color::Blue);
    window->clear(sf::Color::Blue);
    sf::Vector2u size = buffer->getSize();
    currentGame->run();
    buffer->display();
    const sf::Texture& texture = buffer->getTexture();
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);
    window->draw(sprite);


    //sf::sleep(sf::milliseconds(100));
    return true;
}

Program::~Program() {
    delete currentGame;
}

Program::Program(sf::RenderWindow* window) : window(window) {
    buffer = new sf::RenderTexture();
    buffer->create(1024, 768);
    buffer->clear(sf::Color::Blue);
    currentGame = new Game(buffer);
}
