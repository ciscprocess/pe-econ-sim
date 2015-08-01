//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAMESTATE_H
#define PE_ECON_SIM_GAMESTATE_H


#include "game/generation/GameStateSeeder.h"
#include "world/CellularBoard.h"
#include "Unit.h"
#include "GameAction.h"
#include "GameActionQueue.h"
namespace undocked {
    namespace game {
        class GameAction;

        namespace generation {
            class GameStateSeeder;
        }

        using generation::GameStateSeeder;
        using world::CellularBoard;

        class GameState {

        public:
            GameState(int width, int height, GameStateSeeder& seeder);
            void tick();

            CellularBoard *getBoard() const {
                return board;
            }

            void queueAction(GameAction& action, void* key);
            void putAction(GameAction& action, void* key);

            void selectUnit(Unit* unit) {
                selectedUnit = unit;
            };

            std::vector<Unit*> units;
            Unit* selectedUnit;
        private:
            std::map<void*, GameActionQueue> actions;
            CellularBoard* board;

        };
    }
}

#endif //PE_ECON_SIM_GAMESTATE_H
