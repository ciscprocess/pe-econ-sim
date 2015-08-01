/*
 * file: Program.h
 * author: Nathan Korzekwa
 * date: 2015-07-10
 * description:
 * An organization class that neatly wraps game operations and UI updates into a state-managed interface
 */

#ifndef PE_ECON_SIM_PROGRAM_H
#define PE_ECON_SIM_PROGRAM_H


#include "game/Game.h"

namespace undocked {
    using game::Game;

    class Program {

    public:
        Program(sf::RenderWindow* window);
        ~Program();

        bool run();

    private:
        Game* currentGame;
        sf::RenderWindow* window;
        sf::RenderTexture* buffer;

        void windowResizeHandler(sf::Event event);
    };

}

#endif //PE_ECON_SIM_PROGRAM_H
