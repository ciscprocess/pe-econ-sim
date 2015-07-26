//
// Created by Nathan on 7/10/2015.
//

#include <EventManager.h>
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
    buffer->create(window->getSize().x, window->getSize().y);

    buffer->clear(sf::Color::Blue);


    std::function<void (sf::Event)> handler = std::bind(&Program::windowResizeHandler, this, std::placeholders::_1);
    EventManager::getInstance()->addListener(handler);

    currentGame = new Game(buffer);

}

void Program::windowResizeHandler(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        buffer->create(event.size.width, event.size.height);
        buffer->clear(sf::Color::Blue);
    }
}
