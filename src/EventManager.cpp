//
// Created by Nathan on 7/10/2015.
//

#include "EventManager.h"
EventManager* EventManager::INSTANCE = nullptr;

EventManager::EventManager(sf::RenderWindow *window) : window(window) {

}

EventManager* EventManager::getInstance() {
    if (!EventManager::INSTANCE)
        throw new std::exception();
    else
        return EventManager::INSTANCE;
}

EventManager *EventManager::initialize(sf::RenderWindow* window) {
    return INSTANCE = new EventManager(window);
}

void EventManager::addListener(std::function<void (sf::Event)> function) {
    handlers.push_back(function);
}

void EventManager::pollEvents() {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window->close();
        else {
            for (int i = 0; i < handlers.size(); i++) {
                auto f = handlers[i];
                f(event);
            }
        }
    }

    while (eventStack.size() > 0) {
        GameInteractionEvent event = eventStack.back();
        eventStack.pop_back();
        for (int i = 0; i < eventHandlers.size(); i++) {
            auto f = eventHandlers[i];
            f(event);
        }
    }
}

void EventManager::pushEvent(GameInteractionEvent event) {
    eventStack.push_back(event);
}

void EventManager::addInteractionListener(std::function<void(GameInteractionEvent)> listener) {
    eventHandlers.push_back(listener);
}
