//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_CELLULARBOARD_H
#define PE_ECON_SIM_CELLULARBOARD_H

#include <lemon/path.h>
#include "boost/multi_array.hpp"
#include "BoardCell.h"

#include "lemon/list_graph.h"

class CellularBoard {
public:
    CellularBoard(int width, int height);

    BoardCell& getCell(int u, int v) { return ((*grid)[v][u]); };
    void setCell(int u, int v, BoardCell cell) {
        (*grid)[v][u] = cell;
    };

    std::vector<sf::Vector2i> calculatePath(sf::Vector2i start, sf::Vector2i end);

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    bool hasChanged() { return true; }

    void generateAdjacencyGraph();

private:
    boost::multi_array<BoardCell, 2>* grid;
    boost::multi_array<lemon::ListGraph::Node, 2> nodeGrid;
    lemon::ListGraph* adjacencyGraph = nullptr;
    lemon::ListGraph::NodeMap<sf::Vector2i>* nodeMap = nullptr;
    lemon::ListGraph::EdgeMap<double>* costs = nullptr;

    int width, height;

};


#endif //PE_ECON_SIM_CELLULARBOARD_H
