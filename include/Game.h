//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAME_H
#define PE_ECON_SIM_GAME_H

#include "GameState.h"
#include "IsometricSceneVisualizer.h"
#include "GameInteractionEvent.h"

class Game {
public:
    Game(sf::RenderTarget** display);
    bool run();

    void nativeEventHandler(sf::Event);
    void updateRenderTarger(sf::RenderTarget** target) { this->target = target; };

private:
    GameState* state;
    IsometricSceneVisualizer* visualizer;
    sf::RenderTarget** target;
    sf::View gameView;
    sf::Vector2i mouseStart;
    sf::Vector2i mapStart;

    bool middleButtonDown = false;
};


#endif //PE_ECON_SIM_GAME_H
