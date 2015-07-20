//
// Created by Nathan on 7/10/2015.
//

#include <PlainsCell.h>
#include <DesertCell.h>
#include <ForestCell.h>
#include <Civilian.h>
#include "ClusterSeederV2.h"
#include <boost/math/constants/constants.hpp>

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

ClusterSeederV2::ClusterSeederV2() {

}

ClusterSeederV2::~ClusterSeederV2() {

}

void ClusterSeederV2::seedTerrain(GameState *state) {
    CellularBoard *board = state->getBoard();
    int width = board->getWidth(), height = board->getHeight();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);



    AnchorPoint p(sf::Vector2f(board->getWidth() / 2, board->getHeight() / 2));

    // fill in with the default: PlainsCell
    for (int v = 0; v < height; v++) {
        for (int u = 0; u < width; u++) {
            double factor = p.getComponent(sf::Vector2f(u, v));
            board->setCell(u, v, BoardCell(sf::Color(255 * factor, 0, 0)));
        }
    }

/*
    // seed clusters of desert
    int dcc = rand() % 3 + 1;

    for (int i = 0; i < dcc; i++) {
        int cw = rand() % 5 + 3;
        int ch = rand() % 5 + 3;
        int tu = rand() % (width - cw);
        int tv = rand() % (height - ch);

        for (int u = tu; u < tu + cw; u++) {
            for (int v = tv; v < tv + ch; v++) {
                if (dis(gen) < 0.8)
                    board->setCell(u, v, DesertCell());
            }
        }
    }



    // seed clusters of forest
    int fcc = 5 + rand() % 4;

    for (int i = 0; i < fcc; i++) {
        int choice = rand();
        if (choice % 2 == 7) {
            int cw = rand() % 5 + 3;
            int ch = rand() % 5 + 3;
            int tu = rand() % (width - cw);
            int tv = rand() % (height - ch);

            for (int u = tu; u < tu + cw; u++) {
                for (int v = tv; v < tv + ch; v++) {
                    if (dis(gen) < 0.8)
                        board->setCell(u, v, ForestCell());
                }
            }
        } else {
            int cw = rand() % 5 + 3;
            int tu = rand() % (width - cw);
            int tv = rand() % (height - cw);

            for (int u = tu; u <= tu + cw; u++) {
                board->setCell(u, u, ForestCell());
                board->setCell(u, (tu + cw) - (u - tu), ForestCell());
            }
        }

    }


    // propagate the desert and forest terrains
    int iterations = (int)ceil((sqrt(width * height) / 30) * 6);
    for (int iteration = 0; iteration < iterations; iteration++)
    {
        boost::multi_array<std::pair<int, int>, 2> neighbors(boost::extents[height][width]);

        for (int v = 0; v < height; v++) {
            for (int u = 0; u < width; u++) {
                int right = (u + 1) % width;
                int up = (v + 1) % height;
                int down = std::max(v - 1, 0);
                int left = std::max(u - 1, 0);
                int d_incident = 0, f_incident = 0;

                if (board->getCell(right, v).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (board->getCell(right, v).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                if (board->getCell(left, v).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (board->getCell(left, v).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                if (board->getCell(u, up).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (board->getCell(u, up).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                if (board->getCell(u, down).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (board->getCell(u, down).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                neighbors[v][u] = std::make_pair(d_incident, f_incident);
            }
        }

        for (int v = 0; v < height; v++) {
            for (int u = 0; u < width; u++) {
                BoardCell cell = board->getCell(u, v);
                std::pair<int, int> pair = (std::pair<int, int>)neighbors[v][u];
                int d_count = pair.first;
                int f_count = pair.second;

                if (cell.getType() == BoardCell::TYPE::Desert) {
                    if (d_count == 1) {
                        if (dis(gen) < 0)
                            board->setCell(u, v, PlainsCell());

                    }
                    else if (d_count == 0) {
                        board->setCell(u, v, PlainsCell());
                    }
                }
                else if (cell.getType() == BoardCell::TYPE::Plains)
                {
                    if (d_count > 1)
                        board->setCell(u, v, DesertCell());
                    else if (d_count > 0 && dis(gen) > 0.5) {
                        board->setCell(u, v, DesertCell());
                    }
                    else if (f_count > 1) {
                        board->setCell(u, v, ForestCell());
                    }
                    else if (f_count > 0 && dis(gen) > 0.6) {
                        board->setCell(u, v, ForestCell());
                    }

                }
                else if (cell.getType() == BoardCell::TYPE::Forest) {
                    if (d_count > 0)
                        board->setCell(u, v, PlainsCell());
                    else if (f_count == 1 && dis(gen) > 0.9)
                        board->setCell(u, v, PlainsCell());
                    else if (f_count == 0 && dis(gen) > 0.5)
                        board->setCell(u, v, PlainsCell());
                }
            }
        }
    }
    */
}

void ClusterSeederV2::seedInfrastructure(GameState *state) {

}

void ClusterSeederV2::seedUnits(GameState *state) {
    for (int i = 0; i < 10; i++) {
        Civilian* civvie = new Civilian();
        civvie->setLocation(sf::Vector2i(rand() % state->getBoard()->getWidth(), rand() % state->getBoard()->getHeight()));
        state->units.push_back(civvie);
    }
}

double ClusterSeederV2::AnchorPoint::getComponent(sf::Vector2f loc) {
    sf::Vector2f displacement = loc - this->location;
    double theta = std::atan2(displacement.y, displacement.x);
    double num = func(theta) / 2.5;
    return std::min<double>(num, 1);
}

double ClusterSeederV2::AnchorPoint::dSigmoid(double x) {
    return std::exp(x) / ((1 + std::exp(x)) * (1 + std::exp(x)));
}

double ClusterSeederV2::AnchorPoint::func(double theta) {
    double value1 = 0, value2 = 0;
    double PI = boost::math::constants::pi<double>();

    for (auto pair : sizesAndPhases) {
        double size = pair.first;
        double phase = pair.second;
        // warning: some kind of wrapping will be needed for this!
        value1 += size * dSigmoid(10 * (theta - phase));
        value2 += size * dSigmoid(10 * (theta - 2*PI - phase));
    }

    return std::abs(value1) > std::abs(value2) ? value1 : value2;
}

ClusterSeederV2::AnchorPoint::AnchorPoint(sf::Vector2f location) : location(location) {
    typedef boost::mt19937 RNGType;
    RNGType rng(time(0));

    double PI = boost::math::constants::pi<double>();

    boost::uniform_int<> sizeDistribution( 0, 10 );
    boost::variate_generator< RNGType, boost::uniform_int<> > sizeGen(rng, sizeDistribution);

    boost::uniform_int<> phaseDistribution( -PI, PI );
    boost::variate_generator< RNGType, boost::uniform_int<> > phaseGen(rng, phaseDistribution);

    for (int i = 0; i < 10; i++) {
        sizesAndPhases.push_back(std::make_pair(sizeGen(), phaseGen()));
    }
}
