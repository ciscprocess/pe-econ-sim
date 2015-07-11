//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_PROGRAM_H
#define PE_ECON_SIM_PROGRAM_H


#include "Game.h"

class Program {

public:
    Program(sf::RenderWindow* window);
    ~Program();

    bool run(int tick);

private:
    Game* currentGame;
    sf::RenderWindow* window;
    sf::RenderTexture* buffer;
};


#endif //PE_ECON_SIM_PROGRAM_H
