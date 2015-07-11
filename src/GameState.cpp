//
// Created by Nathan on 7/10/2015.
//

#include <ClusterSeederV1.h>
#include "GameState.h"

void GameState::tick() {
    for (int i = 0; i < actions.size(); i++) {
        GameAction& action = actions[i];
        if (!action.tick(this))
            actions.erase(actions.begin() + i--);
        
    }
}

GameState::GameState(int width, int height, GameStateSeeder &seeder) {
    board = new CellularBoard(width, height);
    seeder.seedTerrain(this);
    seeder.seedUnits(this);
    selectedUnit = nullptr;
}
