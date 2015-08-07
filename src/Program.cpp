#include "event/EventManager.h"
#include "Program.h"

namespace undocked {
    using event::EventManager;

    // constructs an application around a given window
    Program::Program(sf::RenderWindow& window) : window(window), uiManager(window.getSize().x, window.getSize().y) {
        sf::Vector2u size = window.getSize();
        buffer.create(size.x, size.y);

        buffer.clear(sf::Color::Blue);

        std::function<void (sf::Event)> handler = std::bind(&Program::windowResizeHandler, this, std::placeholders::_1);
        EventManager::getInstance()->addListener(handler);


        currentGame = new Game(size.x, size.y);
    }

    Program::~Program() {
        delete currentGame;
    }

    // updates rendering objects for resized window
    void Program::windowResizeHandler(sf::Event event) {
        if (event.type == sf::Event::Resized) {
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            buffer.create(event.size.width, event.size.height);
            buffer.clear(sf::Color::Blue);
            uiManager.updateSize(event.size.width, event.size.height);
        }
    }

    // executes all tasks needed for the current time-limited tick
    bool Program::run() {
        buffer.clear(sf::Color::Blue);
        window.clear(sf::Color::Blue);

        currentGame->run();
        buffer.draw(*currentGame);
        buffer.display();

        const sf::Texture& texture = buffer.getTexture();
        sf::Sprite sprite(texture);
        sprite.setPosition(0, 0);
        window.draw(sprite);

        return true;
    }
}