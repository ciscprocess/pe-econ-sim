//
// Created by Nathan on 7/10/2015.
//

#include "CellularBoard.h"

#include "lemon/bfs.h"


CellularBoard::CellularBoard(int width, int height) : width(width), height(height), nodeGrid(boost::extents[height][width]) {
    grid = new boost::multi_array<BoardCell, 2>(boost::extents[height][width]);
}

void CellularBoard::generateAdjacencyGraph() {
    using namespace lemon;
    ListGraph *graph = new ListGraph();
    ListGraph::NodeMap<sf::Vector2i>* map = new ListGraph::NodeMap<sf::Vector2i>(*graph);

    for (int u = 0; u < width; u++) {
        for (int v = 0; v < height; v++) {
            nodeGrid[v][u] = graph->addNode();
            (*map)[nodeGrid[v][u]] = sf::Vector2i(u, v);
        }
    }

    for (int u = 1; u < width; u++) {
        for (int v = 1; v < height; v++) {
            if (this->getCell(u, v).getTraversable()) {

                if (this->getCell(u - 1, v).getTraversable()) {
                    graph->addEdge(nodeGrid[v][u - 1], nodeGrid[v][u]);
                }

                if (this->getCell(u, v - 1).getTraversable()) {
                    graph->addEdge(nodeGrid[v - 1][u], nodeGrid[v][u]);
                }

                if (this->getCell(u- 1, v - 1).getTraversable()) {
                    graph->addEdge(nodeGrid[v - 1][u - 1], nodeGrid[v][u]);
                }
            }
        }
    }

    for (int u = 0; u < width - 1; u++) {
        for (int v = 1; v < width; v++) {
            if (this->getCell(u + 1, v - 1).getTraversable()) {
                graph->addEdge(nodeGrid[v - 1][u + 1], nodeGrid[v][u]);
            }
        }
    }



    adjacencyGraph = graph;
    nodeMap = map;
}

std::vector<sf::Vector2i> CellularBoard::calculatePath(sf::Vector2i start, sf::Vector2i end) {
    using namespace lemon;

    ListGraph::Node startNode = nodeGrid[start.y][start.x];
    ListGraph::Node endNode = nodeGrid[end.y][end.x];
    Bfs<ListGraph> bfs(*adjacencyGraph);


    bfs.run(startNode);

    std::vector<sf::Vector2i> path;

    ListPath<ListGraph> intPath = bfs.path(endNode);

    for (int i = 0; i < intPath.length(); i++) {
        ListGraph::Node target = adjacencyGraph->target(intPath.nth(i));
        path.push_back((*nodeMap)[target]);
    }

    return path;
}
