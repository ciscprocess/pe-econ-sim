//
// Created by Nathan on 7/10/2015.
//

#include "world/PlainsCell.h"
#include "world/DesertCell.h"
#include "world/ForestCell.h"
#include "game/Civilian.h"
#include "game/generation/ClusterSeederV2.h"
#include <boost/math/constants/constants.hpp>
#include <numeric/Random.h>
#include <boost/generator_iterator.hpp>


namespace undocked {
    namespace game {
        namespace generation {
            numeric::Random random(200);

            using namespace world;

            ClusterSeederV2::ClusterSeederV2() {

            }

            ClusterSeederV2::~ClusterSeederV2() {

            }

            void ClusterSeederV2::seedTerrain(GameState *state) {
                CellularBoard *board = state->getBoard();
                int width = board->getWidth(), height = board->getHeight();


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
                int dcc = 1 + (random.get() > 0.5 ? 0 : 1);

                auto widthGen = random.createUniformInteger(3, 7);
                for (int i = 0; i < dcc; i++) {
                    int cw = widthGen();
                    int ch = widthGen();

                    random.setUniform(0, width - cw - 1);
                    int tu = random.getUniformInteger();

                    random.setUniform(0, width - ch - 1);
                    int tv = random.getUniformInteger();

                    int cx = tu + cw / 2;
                    int cy = tv + ch / 2;
                    AnchorPoint *current = new AnchorPoint(sf::Vector2f(cx, cy));

                    desertAnchors.push_back(current);

                    for (int u = tu; u < tu + cw; u++) {
                        for (int v = tv; v < tv + ch; v++) {
                            if (random.get() < 0.8)
                                board->setCell(u, v, DesertCell());
                        }
                    }
                }

                // seed clusters of forest
                random.setUniform(2, 6);
                int fcc = random.getUniformInteger();

                for (int i = 0; i < fcc; i++) {
                    int cw = widthGen();
                    int ch = widthGen();
                    random.setUniform(0, width - cw - 1);
                    int tu = random.getUniformInteger();

                    random.setUniform(0, width - ch - 1);
                    int tv = random.getUniformInteger();

                    int cx = tu + cw / 2;
                    int cy = tv + ch / 2;
                    AnchorPoint *current = new AnchorPoint(sf::Vector2f(cx, cy));

                    anchors.push_back(current);

                    for (int u = tu; u < tu + cw; u++) {
                        for (int v = tv; v < tv + ch; v++) {
                            if (random.get() < 0.8)
                                board->setCell(u, v, ForestCell());
                        }
                    }
                }

                for (int v = 0; v < height; v++) {
                    for (int u = 0; u < width; u++) {
                        AnchorPoint *closest = nullptr;
                        double minDist = 999999;
                        for (auto anchor : anchors) {
                            double dist = std::abs(anchor->location.x - u) + std::abs(anchor->location.y - v);
                            if (dist < minDist) {
                                closest = anchor;
                                minDist = dist;
                            }
                        }

                        closestAnchors[v][u] = closest;
                    }
                }


                for (int v = 0; v < height; v++) {
                    for (int u = 0; u < width; u++) {
                        AnchorPoint *closest = nullptr;
                        double minDist = 999999;
                        for (auto anchor : desertAnchors) {
                            double dist = std::abs(anchor->location.x - u) + std::abs(anchor->location.y - v);
                            if (dist < minDist) {
                                closest = anchor;
                                minDist = dist;
                            }
                        }
                        closestDesertAnchors[v][u] = closest;
                    }
                }


                // propagate the desert and forest terrains
                int iterations = (int) ceil((sqrt(width * height) / 40) * 6) * 3;
                int ruleSet = 0;
                for (int iteration = 0; iteration < iterations; iteration++) {
                    boost::multi_array<std::pair<int, int>, 2> neighbors(boost::extents[height][width]);

                    for (int v = 0; v < height; v++) {
                        for (int u = 0; u < width; u++) {
                            int right = (u + 1);
                            int up = (v + 1);
                            int down = v - 1;
                            int left = u - 1;
                            int d_incident = 0, f_incident = 0;

                            auto in = [height, width](int a, bool isUp) {
                                if (isUp) {
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
                                std::pair<int, int> pair = (std::pair<int, int>) neighbors[v][u];
                                int d_count = pair.first;
                                int f_count = pair.second;

                                if (cell.getType() == BoardCell::TYPE::Desert) {
                                    if (d_count == 1) {
                                        if (random.get() < 0)
                                            board->setCell(u, v, PlainsCell());

                                    }
                                    else if (d_count == 0) {
                                        board->setCell(u, v, PlainsCell());
                                    }
                                }
                                else if (cell.getType() == BoardCell::TYPE::Plains) {
                                    AnchorPoint *p = closestAnchors[v][u];
                                    AnchorPoint *dp = closestDesertAnchors[v][u];
                                    if (d_count > 1 && dp->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1)
                                        board->setCell(u, v, DesertCell());
                                    else if (d_count > 0 && dp->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1 && random.get() > 0.5) {
                                        board->setCell(u, v, DesertCell());
                                    }
                                    else if (f_count > 1 && p->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1) {
                                        board->setCell(u, v, ForestCell());
                                    }
                                    else if (f_count > 0 && p->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1 && random.get() > 0.5) {
                                        board->setCell(u, v, ForestCell());
                                    }

                                }
                                else if (cell.getType() == BoardCell::TYPE::Forest) {
                                    if (d_count > 0)
                                        board->setCell(u, v, PlainsCell());
                                    else if (f_count == 1 && random.get() > 0.9)
                                        board->setCell(u, v, PlainsCell());
                                    else if (f_count == 0 && random.get() > 0.5)
                                        board->setCell(u, v, PlainsCell());
                                }
                            }
                        }
                    } else {
                        for (int v = 0; v < height; v++) {
                            for (int u = 0; u < width; u++) {
                                BoardCell cell = board->getCell(u, v);
                                std::pair<int, int> pair = (std::pair<int, int>) neighbors[v][u];
                                int d_count = pair.first;
                                int f_count = pair.second;

                                if (cell.getType() == BoardCell::TYPE::Desert) {
                                    if (d_count == 1) {
                                        if (random.get() < 0.5)
                                            board->setCell(u, v, PlainsCell());
                                    }
                                    else if (d_count == 0) {
                                        board->setCell(u, v, PlainsCell());
                                    }
                                }
                                else if (cell.getType() == BoardCell::TYPE::Plains) {
                                    AnchorPoint *p = closestAnchors[v][u];
                                    AnchorPoint *dp = closestDesertAnchors[v][u];
                                    if (d_count > 1 && dp->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1)
                                        board->setCell(u, v, DesertCell());
                                    else if (d_count > 0 && dp->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1 && random.get() > 0.5) {
                                        board->setCell(u, v, DesertCell());
                                    }
                                    else if (f_count > 1 && p->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1) {
                                        board->setCell(u, v, ForestCell());
                                    }
                                    else if (f_count > 0 && p->getComponent(sf::Vector2f(u, v)) > random.get() + 0.1 && random.get() > 0.5) {
                                        board->setCell(u, v, ForestCell());
                                    }

                                }
                                else if (cell.getType() == BoardCell::TYPE::Forest) {
                                    if (d_count > 0)
                                        board->setCell(u, v, PlainsCell());
                                    else if (f_count == 1 && random.get() > 0.7)
                                        board->setCell(u, v, PlainsCell());
                                    else if (f_count == 0 && random.get() > 0.4)
                                        board->setCell(u, v, PlainsCell());
                                }
                            }
                        }
                    }
                }

                board->generateAdjacencyGraph();

                // clean up
                for (auto anchor : desertAnchors) {
                    delete anchor;
                }

                for (auto anchor : anchors) {
                    delete anchor;
                }
            }

            void ClusterSeederV2::seedInfrastructure(GameState *state) {

            }

            void ClusterSeederV2::seedUnits(GameState *state) {
                int width = state->getBoard()->getWidth(),
                        height = state->getBoard()->getHeight();

                auto widthGen = random.createUniformInteger(4, 8);
                int cw = widthGen();
                int ch = widthGen();

                int tu = random.createUniformInteger(0, width - cw - 1)();
                int tv = random.createUniformInteger(0, height - ch - 1)();

                std::vector<int> locations((unsigned) cw * ch);
                std::iota(locations.begin(), locations.end(), 0);

                // random_shuffle should not be used, as it utilized rand()
                std::random_shuffle(locations.begin(), locations.end());

                for (int i = 0; i < 10; i++) {
                    Civilian *civvie = new Civilian();
                    int u = tu + locations[i] % cw,
                            v = tv + locations[i] / cw;
                    civvie->setLocation(sf::Vector2i(u, v));
                    state->units.push_back(civvie);
                }

                std::sort(state->units.begin(), state->units.end(), [](Unit* a, Unit* b) {
                    return a->getLocation().y < b->getLocation().y;
                });
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
                    value2 += size * dSigmoid(10 * (theta - 2 * PI - phase));
                }

                // two values in case a sigmoid function borders PI or -PI
                return std::abs(value1) > std::abs(value2) ? value1 : value2;
            }

            ClusterSeederV2::AnchorPoint::AnchorPoint(sf::Vector2f location) : location(location) {
                double PI = boost::math::constants::pi<double>();

                auto sizeGen = random.createUniformDouble(-0.5, 12);
                auto phaseGen = random.createUniformDouble(-PI, PI);

                for (int i = 0; i < 10; i++) {
                    sizesAndPhases.push_back(std::make_pair(sizeGen(), phaseGen()));
                }
            }

        }
    }
}