//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_CELLULARBOARD_H
#define PE_ECON_SIM_CELLULARBOARD_H
#include "boost/multi_array.hpp"
#include "BoardCell.h"

class CellularBoard {
public:
    CellularBoard(int width, int height);

    BoardCell& getCell(int u, int v) { return ((*grid)[v][u]); };
    void setCell(int u, int v, BoardCell cell) {
        (*grid)[v][u] = cell;
    };

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    bool hasChanged() { return true; }

private:
    boost::multi_array<BoardCell, 2>* grid;
    int width, height;

    void generateAdjacencyGraph();
};


#endif //PE_ECON_SIM_CELLULARBOARD_H
