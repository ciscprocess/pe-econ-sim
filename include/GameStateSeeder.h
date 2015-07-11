//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAMESTATESEEDER_H
#define PE_ECON_SIM_GAMESTATESEEDER_H


#include "GameState.h"

class GameState;
class GameStateSeeder {
public:
    virtual void seedTerrain(GameState *state) = 0;
    virtual void seedInfrastructure(GameState *state) = 0;
    virtual void seedUnits(GameState *state) = 0;

    virtual void seedAll(GameState *state)
    {
        seedTerrain(state);
        seedInfrastructure(state);
        seedUnits(state);
    }
};


#endif //PE_ECON_SIM_GAMESTATESEEDER_H
