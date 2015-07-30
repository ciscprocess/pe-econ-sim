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


    typedef boost::mt19937 RNGType;
    RNGType rng(rand());


    boost::uniform_real<> dist( 0, 1 );
    boost::variate_generator< RNGType, boost::uniform_real<> > gen(rng, dist);

    double val = gen();


    std::vector<AnchorPoint*> anchors;
    boost::multi_array<AnchorPoint*, 2> closestAnchors(boost::extents[height][width]);

    std::vector<AnchorPoint*> desertAnchors;
    boost::multi_array<AnchorPoint*, 2> closestDesertAnchors(boost::extents[height][width]);


    // fill in with the default: PlainsCell
    for (int v = 0; v < height; v++) {
        for (int u = 0; u < width; u++) {
            board->setCell(u, v, PlainsCell());
        }
    }


    // seed clusters of desert
    int dcc = 1 + rand() % 2;

    for (int i = 0; i < dcc; i++) {
        int cw = rand() % 5 + 3;
        int ch = rand() % 5 + 3;
        int tu = rand() % (width - cw);
        int tv = rand() % (height - ch);

        int cx = tu + cw / 2;
        int cy = tv + ch / 2;
        AnchorPoint* current = new AnchorPoint(sf::Vector2f(cx, cy));

        desertAnchors.push_back(current);

        for (int u = tu; u < tu + cw; u++) {
            for (int v = tv; v < tv + ch; v++) {
                if (gen() < 0.8)
                    board->setCell(u, v, DesertCell());
            }
        }
    }



    // seed clusters of forest
    int fcc = rand() % 2 + 5;

    for (int i = 0; i < fcc; i++) {
        int cw = rand() % 5 + 3;
        int ch = rand() % 5 + 3;
        int tu = rand() % (width - cw);
        int tv = rand() % (height - ch);
        int cx = tu + cw / 2;
        int cy = tv + ch / 2;
        AnchorPoint* current = new AnchorPoint(sf::Vector2f(cx, cy));

        anchors.push_back(current);

        for (int u = tu; u < tu + cw; u++) {
            for (int v = tv; v < tv + ch; v++) {
                if (gen() < 0.8)
                    board->setCell(u, v, ForestCell());
            }
        }
    }

    for (int v = 0; v < height; v++) {
        for (int u = 0; u < width; u++) {
            AnchorPoint* closest = nullptr;
            double minDist = 999999;
            for (auto anchor : anchors) {
                double dist = std::abs(anchor->location.x - u) + std::abs(anchor->location.y - v);
                if (dist < minDist) {
                    closest = anchor;
                    minDist = dist;
                }
            }

            //board->setCell(u, v, BoardCell(sf::Color(closest->getComponent(sf::Vector2f(u, v)) * 255, 0, 0)));
            closestAnchors[v][u] = closest;
        }
    }


    for (int v = 0; v < height; v++) {
        for (int u = 0; u < width; u++) {
            AnchorPoint* closest = nullptr;
            double minDist = 999999;
            for (auto anchor : desertAnchors) {
                double dist = std::abs(anchor->location.x - u) + std::abs(anchor->location.y - v);
                if (dist < minDist) {
                    closest = anchor;
                    minDist = dist;
                }
            }


            //board->setCell(u, v, BoardCell(sf::Color(closest->getComponent(sf::Vector2f(u, v)) * 255, 0, 0)));
            closestDesertAnchors[v][u] = closest;
        }
    }



    //return;
    // propagate the desert and forest terrains
    int iterations = (int)ceil((sqrt(width * height) / 40) * 6) * 3;
    int ruleSet = 0;
    for (int iteration = 0; iteration < iterations; iteration++)
    {
        boost::multi_array<std::pair<int, int>, 2> neighbors(boost::extents[height][width]);

        for (int v = 0; v < height; v++) {
            for (int u = 0; u < width; u++) {
                int right = (u + 1);
                int up = (v + 1);
                int down = v - 1;
                int left = u - 1;
                int d_incident = 0, f_incident = 0;

                auto in = [height, width](int a, bool up) {
                    if (up) {
                        return a >= 0 && a < height;
                    } else {
                        return a >= 0 && a < width;
                    }
                };

                if (in(right, 0) && board->getCell(right, v).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (in(right, 0) && board->getCell(right, v).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                if (in(left, 0) && board->getCell(left, v).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (in(left, 0) && board->getCell(left, v).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                if (in(up, 1) && board->getCell(u, up).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (in(up, 1) && board->getCell(u, up).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                if (in(down, 1) && board->getCell(u, down).getType() == BoardCell::TYPE::Desert) {
                    d_incident += 1;
                }
                else if (in(down, 1) && board->getCell(u, down).getType() == BoardCell::TYPE::Forest) {
                    f_incident += 1;
                }

                neighbors[v][u] = std::make_pair(d_incident, f_incident);
            }
        }


        if ((iteration % 8) == 0) ruleSet = !ruleSet;

        if (ruleSet == 0) {
            for (int v = 0; v < height; v++) {
                for (int u = 0; u < width; u++) {
                    BoardCell cell = board->getCell(u, v);
                    std::pair<int, int> pair = (std::pair<int, int>)neighbors[v][u];
                    int d_count = pair.first;
                    int f_count = pair.second;

                    if (cell.getType() == BoardCell::TYPE::Desert) {
                        if (d_count == 1) {
                            if (gen() < 0)
                                board->setCell(u, v, PlainsCell());

                        }
                        else if (d_count == 0) {
                            board->setCell(u, v, PlainsCell());
                        }
                    }
                    else if (cell.getType() == BoardCell::TYPE::Plains)
                    {
                        AnchorPoint* p = closestAnchors[v][u];
                        AnchorPoint* dp = closestDesertAnchors[v][u];
                        if (d_count > 1 && dp->getComponent(sf::Vector2f(u, v)) > gen() + 0.1)
                            board->setCell(u, v, DesertCell());
                        else if (d_count > 0 && dp->getComponent(sf::Vector2f(u, v)) > gen() + 0.1 && gen() > 0.5) {
                            board->setCell(u, v, DesertCell());
                        }
                        else if (f_count > 1 && p->getComponent(sf::Vector2f(u, v)) > gen() + 0.1) {
                            board->setCell(u, v, ForestCell());
                        }
                        else if (f_count > 0 && p->getComponent(sf::Vector2f(u, v)) > gen() + 0.1  && gen() > 0.5) {
                            board->setCell(u, v, ForestCell());
                        }

                    }
                    else if (cell.getType() == BoardCell::TYPE::Forest) {
                        if (d_count > 0)
                            board->setCell(u, v, PlainsCell());
                        else if (f_count == 1 && gen() > 0.9)
                            board->setCell(u, v, PlainsCell());
                        else if (f_count == 0 && gen() > 0.5)
                            board->setCell(u, v, PlainsCell());
                    }
                }
            }
        } else {
            for (int v = 0; v < height; v++) {
                for (int u = 0; u < width; u++) {
                    BoardCell cell = board->getCell(u, v);
                    std::pair<int, int> pair = (std::pair<int, int>)neighbors[v][u];
                    int d_count = pair.first;
                    int f_count = pair.second;

                    if (cell.getType() == BoardCell::TYPE::Desert) {
                        if (d_count == 1) {
                            if (gen() < 0.5)
                                board->setCell(u, v, PlainsCell());

                        }
                        else if (d_count == 0) {
                            board->setCell(u, v, PlainsCell());
                        }
                    }
                    else if (cell.getType() == BoardCell::TYPE::Plains)
                    {
                        AnchorPoint* p = closestAnchors[v][u];
                        AnchorPoint* dp = closestDesertAnchors[v][u];
                        if (d_count > 1 && dp->getComponent(sf::Vector2f(u, v)) > gen() + 0.1)
                            board->setCell(u, v, DesertCell());
                        else if (d_count > 0 && dp->getComponent(sf::Vector2f(u, v)) > gen() + 0.1 && gen() > 0.5) {
                            board->setCell(u, v, DesertCell());
                        }
                        else if (f_count > 1 && p->getComponent(sf::Vector2f(u, v)) > gen() + 0.1) {
                            board->setCell(u, v, ForestCell());
                        }
                        else if (f_count > 0 && p->getComponent(sf::Vector2f(u, v)) > gen() + 0.1  && gen() > 0.5) {
                            board->setCell(u, v, ForestCell());
                        }

                    }
                    else if (cell.getType() == BoardCell::TYPE::Forest) {
                        if (d_count > 0)
                            board->setCell(u, v, PlainsCell());
                        else if (f_count == 1 && gen() > 0.7)
                            board->setCell(u, v, PlainsCell());
                        else if (f_count == 0 && gen() > 0.4)
                            board->setCell(u, v, PlainsCell());
                    }
                }
            }
        }
    }

    board->generateAdjacencyGraph();
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
    double num = func(theta) / 3.5;
    return std::min<double>(num, 1);
}

double ClusterSeederV2::AnchorPoint::dSigmoid(double x) {
    return std::exp(x) / ((1 + std::exp(x)) * (1 + std::exp(x)));
}

double ClusterSeederV2::AnchorPoint::func(double theta) {
    double value1 = 1, value2 = 1;
    double PI = boost::math::constants::pi<double>();

    for (auto pair : sizesAndPhases) {
        double size = pair.first;
        double phase = pair.second;

        // warning: some kind of wrapping will be needed for this!
        // this might explain some of the harsh edges seen; however this is a minor problem
        value1 += size * dSigmoid(10 * (theta - phase));
        value2 += size * dSigmoid(10 * (theta - 2*PI - phase));
    }

    // two values in case a sigmoid function borders PI or -PI
    return std::abs(value1) > std::abs(value2) ? value1 : value2;
}

typedef boost::mt19937 RNGType;
RNGType rng(time(0));

double PI = boost::math::constants::pi<double>();

boost::uniform_real<> sizeDistribution( -0.5, 12 );
boost::variate_generator< RNGType, boost::uniform_real<> > sizeGen(rng, sizeDistribution);

boost::uniform_real<> phaseDistribution( -PI, PI );
boost::variate_generator< RNGType, boost::uniform_real<> > phaseGen(rng, phaseDistribution);

ClusterSeederV2::AnchorPoint::AnchorPoint(sf::Vector2f location) : location(location) {
    for (int i = 0; i < 10; i++) {
        sizesAndPhases.push_back(std::make_pair(sizeGen(), phaseGen()));
    }
}
