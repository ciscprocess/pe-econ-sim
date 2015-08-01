//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_EVENTMANAGER_H
#define PE_ECON_SIM_EVENTMANAGER_H
#include "SFML/Graphics.hpp"
#include "GameInteractionEvent.h"

#include <functional>

namespace undocked {
namespace event {
    class EventManager {

    public:
        EventManager(sf::RenderWindow *window);

        static EventManager *initialize(sf::RenderWindow *window);

        static EventManager *getInstance();

        void addListener(std::function<void(sf::Event)>);

        void pollEvents();

        void pushEvent(GameInteractionEvent event);

        void addInteractionListener(std::function<void(GameInteractionEvent)> listener);

    private:
        static EventManager *INSTANCE;
        sf::RenderWindow *window;
        std::vector<GameInteractionEvent> eventStack;
        std::vector<std::function<void(sf::Event)> > handlers;
        std::vector<std::function<void(GameInteractionEvent)> > eventHandlers;

    };
}
}
#endif //PE_ECON_SIM_EVENTMANAGER_H
