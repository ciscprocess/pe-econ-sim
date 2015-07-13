//
// Created by Nathan on 7/12/2015.
//

#include "GameActionQueue.h"

GameActionQueue::GameActionQueue(void *key) {

}

bool GameActionQueue::tick(GameState* state) {
    GameAction& action = queue.back();
    if (!action.tick(state))
        queue.pop_back();

    return !queue.empty();
}
