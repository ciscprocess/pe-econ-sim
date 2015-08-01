//
// Created by Nathan on 7/11/2015.
//

#ifndef PE_ECON_SIM_GAMEACTION_H
#define PE_ECON_SIM_GAMEACTION_H

#include <functional>

namespace undocked {
    namespace game {
        class GameState;

        class GameAction {
        public:
            GameAction(std::function<bool (GameState*)> tickAction, int turns = -1);

            bool tick(GameState* state) {

                return --turns != 0 && tickAction(state);
            }
        private:
            int turns;
            std::function<bool (GameState*)> tickAction;
        };

    }
}



#endif //PE_ECON_SIM_GAMEACTION_H
