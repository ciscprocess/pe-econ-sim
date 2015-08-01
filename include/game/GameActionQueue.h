//
// Created by Nathan on 7/12/2015.
//

#ifndef PE_ECON_SIM_GAMEACTIONQUEUE_H
#define PE_ECON_SIM_GAMEACTIONQUEUE_H
#include <vector>

#include "GameAction.h"

namespace undocked {
    namespace game {
        class GameActionQueue {
        public:
            GameActionQueue(void* key = nullptr);

            void clear() { queue.clear(); };
            void add(GameAction action) { queue.insert(queue.begin(), action); };
            bool tick(GameState* state);

        private:
            // TODO: implement common base class and use that instead of void*
            void* key;

            std::vector<GameAction> queue;
        };
    }
}



#endif //PE_ECON_SIM_GAMEACTIONQUEUE_H
