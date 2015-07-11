#include <SFML/Graphics.hpp>

#include "Program.h"

#include "EventManager.h"



int main()
{
    srand(time(NULL));
    int tick = 0;
    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");

    EventManager::initialize(&window);
    EventManager* eventManager = EventManager::getInstance();
    Program simulator(&window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        eventManager->pollEvents();
        if (!simulator.run(tick = 0))
            window.close();

        if (tick == 0)
            window.display();
    }

    return 0;
}