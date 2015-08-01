//
// Created by Nathan on 7/10/2015.
//

#include "game/GameState.h"

void GameState::tick() {
    for (std::map<void*, GameActionQueue>::iterator i = actions.begin(); i != actions.end(); i++) {
        GameActionQueue& action = i->second;
        if (!action.tick(this)) {
            actions.erase(i--);
            if (actions.size() < 1)
                break;
        }


    }
}

GameState::GameState(int width, int height, GameStateSeeder &seeder) {
    board = new CellularBoard(width, height);
    seeder.seedTerrain(this);
    seeder.seedUnits(this);
    selectedUnit = nullptr;
}

void GameState::queueAction(GameAction &action, void* key) {
    if (actions.count(key) == 0) {
        actions[key] = GameActionQueue(key);
    }

    GameActionQueue& queue = actions[key];
    queue.add(action);
}

void GameState::putAction(GameAction &action, void* key) {
    actions[key] = GameActionQueue(key);

    GameActionQueue& queue = actions[key];
    queue.add(action);
}
