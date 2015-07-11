//
// Created by Nathan on 7/10/2015.
//

#include "CellularBoard.h"

CellularBoard::CellularBoard(int width, int height) : width(width), height(height) {
    grid = new boost::multi_array<BoardCell, 2>(boost::extents[height][width]);
}
