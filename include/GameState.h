//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAMESTATE_H
#define PE_ECON_SIM_GAMESTATE_H


#include "GameStateSeeder.h"
#include "CellularBoard.h"
#include "Unit.h"
#include "GameAction.h"

class GameAction;
class GameStateSeeder;
class GameState {

public:
    GameState(int width, int height, GameStateSeeder& seeder);
    void tick();

    CellularBoard *getBoard() const {
        return board;
    }

    void addAction(GameAction& action) { actions.push_back(action); };
    void selectUnit(Unit* unit) {
        selectedUnit = unit;
    };

    std::vector<Unit*> units;
    Unit* selectedUnit;
private:
    std::vector<GameAction> actions;
    CellularBoard* board;

};


#endif //PE_ECON_SIM_GAMESTATE_H
