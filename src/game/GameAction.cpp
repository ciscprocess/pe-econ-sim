//
// Created by Nathan on 7/11/2015.
//

#include "game/GameAction.h"

namespace undocked {
    namespace game {
        GameAction::GameAction(std::function<bool (GameState *)> tickAction, int turns) : tickAction(tickAction), turns(turns) {

        }
    }
}