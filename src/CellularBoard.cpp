//
// Created by Nathan on 7/10/2015.
//

#include "CellularBoard.h"

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"

CellularBoard::CellularBoard(int width, int height) : width(width), height(height) {
    grid = new boost::multi_array<BoardCell, 2>(boost::extents[height][width]);
}

void CellularBoard::generateAdjacencyGraph() {
    using namespace boost;
    //create an -undirected- graph type, using vectors as the underlying containers
    //and an adjacency_list as the basic representation
    typedef adjacency_list<vecS, vecS, undirectedS> UndirectedGraph;

    //An edge is just a connection between two vertitices. Our verticies above
    //are an enum, and are just used as integers, so our edges just become
    //a std::pair<int, int>
    typedef std::pair<int, int> Edge;


    int N = 0;
    //Example uses an array, but we can easily use another container type
    //to hold our edges.
    std::vector<Edge> edgeVec;
    for (int v = 0; v < this->height; v++) {
        for (int u = 0; u < this->width; u++) {
            BoardCell cell = getCell(u, v);
            if (cell.getType() == BoardCell::TYPE::Plains || cell.getType() == BoardCell::TYPE::Desert) {

            }

        }
    }

    //Now we can initialize our graph using iterators from our above vector
    UndirectedGraph g(edgeVec.begin(), edgeVec.end(), N);

}
