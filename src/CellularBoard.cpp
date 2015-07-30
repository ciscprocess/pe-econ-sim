//
// Created by Nathan on 7/10/2015.
//

#include "CellularBoard.h"

#include "lemon/dijkstra.h"


CellularBoard::CellularBoard(int width, int height) : width(width), height(height), nodeGrid(boost::extents[height][width]) {
    grid = new boost::multi_array<BoardCell, 2>(boost::extents[height][width]);
}

void CellularBoard::generateAdjacencyGraph() {
    using namespace lemon;
    ListGraph *graph = new ListGraph();
    ListGraph::NodeMap<sf::Vector2i>* map = new ListGraph::NodeMap<sf::Vector2i>(*graph);
    ListGraph::EdgeMap<double>* weights = new ListGraph::EdgeMap<double>(*graph);

    for (int u = 0; u < width; u++) {
        for (int v = 0; v < height; v++) {
            nodeGrid[v][u] = graph->addNode();
            (*map)[nodeGrid[v][u]] = sf::Vector2i(u, v);
        }
    }

    for (int u = 0; u < width; u++) {
        for (int v = 0; v < height; v++) {
            if (this->getCell(u, v).getTraversable()) {

                if (u - 1 >= 0 && getCell(u - 1, v).getTraversable()) {
                    auto edge = graph->addEdge(nodeGrid[v][u - 1], nodeGrid[v][u]);
                    (*weights)[edge] = 1;

                    if (getCell(u - 1, v).getType() == BoardCell::TYPE::Forest) {
                        (*weights)[edge] *=2;
                    }
                }

                if (v - 1 >= 0 && getCell(u, v - 1).getTraversable()) {
                    auto edge = graph->addEdge(nodeGrid[v - 1][u], nodeGrid[v][u]);
                    (*weights)[edge] = 1;

                    if (getCell(u, v - 1).getType() == BoardCell::TYPE::Forest) {
                        (*weights)[edge] *=2;
                    }
                }

                if (v - 1 >= 0 && u - 1 >= 0 && getCell(u- 1, v - 1).getTraversable()) {
                    auto edge = graph->addEdge(nodeGrid[v - 1][u - 1], nodeGrid[v][u]);
                    (*weights)[edge] = std::sqrt(2);
                    if (getCell(u - 1, v - 1).getType() == BoardCell::TYPE::Forest) {
                        (*weights)[edge] *=2;
                    }
                }

                if (u + 1 < width && v - 1 >= 0 && getCell(u + 1, v - 1).getTraversable()) {
                    auto edge = graph->addEdge(nodeGrid[v - 1][u + 1], nodeGrid[v][u]);
                    (*weights)[edge] = std::sqrt(2);

                    if (getCell(u + 1, v - 1).getType() == BoardCell::TYPE::Forest) {
                        (*weights)[edge] *=2;
                    }
                }
            }
        }
    }

    adjacencyGraph = graph;
    nodeMap = map;
    costs = weights;
}

std::vector<sf::Vector2i> CellularBoard::calculatePath(sf::Vector2i start, sf::Vector2i end) {
    using namespace lemon;

    ListGraph::Node startNode = nodeGrid[start.y][start.x];
    ListGraph::Node endNode = nodeGrid[end.y][end.x];

    std::vector<sf::Vector2i> path;

    ListPath<ListGraph> intPath;

    dijkstra(*adjacencyGraph, *costs).path(intPath).run(startNode, endNode);

    for (int i = 0; i < intPath.length(); i++) {
        ListGraph::Node target = adjacencyGraph->target(intPath.nth(i));
        path.push_back((*nodeMap)[target]);
    }

    return path;
}
