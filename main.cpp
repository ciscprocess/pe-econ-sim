/*
 * file: main.cpp
 * author: Nathan Korzekwa
 * date: 2015-07-10
 * description:
 * the executable for pe-econ-sim, an experimental economy simulator by NP-Undocked
 */
#include <SFML/Graphics.hpp>

#include "Program.h"

#include "event/EventManager.h"

int main() {
    srand((unsigned) time(NULL));
    std::srand ( unsigned ( std::time(0) ) );

    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "pe-econ-sim 0.1.0pre");

    EventManager::initialize(&window);
    EventManager* eventManager = EventManager::getInstance();
    Program simulator(&window);

    // run the program as long as the window is open
    while (window.isOpen()) {
        eventManager->pollEvents();

        if (!simulator.run()) {
            window.close();
        }

        window.display();
    }

    return 0;
}