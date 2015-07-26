//
// Created by Nathan on 7/10/2015.
//

#include <EventManager.h>
#include "Program.h"

bool Program::run() {
    buffer->clear(sf::Color::Blue);
    window->clear(sf::Color::White);

    //currentGame->run();

    buffer->display();

    const sf::Texture& texture = buffer->getTexture();

    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(1, 1);

    window->draw(sprite);

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
    //currentGame = new Game((sf::RenderTarget**)&buffer);

}

void Program::windowResizeHandler(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        delete buffer;
        buffer = new sf::RenderTexture();
        buffer->create(event.size.height, event.size.height);
        buffer->clear(sf::Color::Blue);
        //currentGame->updateRenderTarger(buffer);
    }
}
