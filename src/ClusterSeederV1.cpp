//
// Created by Nathan on 7/10/2015.
//

#include "world/PlainsCell.h"
#include "world/DesertCell.h"
#include "world/ForestCell.h"
#include "game/Civilian.h"
#include "game/generation/ClusterSeederV1.h"

ClusterSeederV1::ClusterSeederV1() {

}

ClusterSeederV1::~ClusterSeederV1() {

}

void ClusterSeederV1::seedTerrain(GameState *state) {
    CellularBoard *board = state->getBoard();
    int width = board->getWidth(), height = board->getHeight();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    // fill in with the default: PlainsCell
    for (int v = 0; v < height; v++)
    {
        for (int u = 0; u < width; u++)
        {
            board->setCell(u, v, PlainsCell());
        }
    }

    // seed clusters of desert
    int dcc = rand() % 3 + 1;

    for (int i = 0; i < dcc; i++)
    {
        int cw = rand() % 5 + 3;
        int ch = rand() % 5 + 3;
        int tu = rand() % (width - cw);
        int tv = rand() % (height - ch);

        for (int u = tu; u < tu + cw; u++)
        {
            for (int v = tv; v < tv + ch; v++)
            {
                if (dis(gen) < 0.8)
                    board->setCell(u, v, DesertCell());
            }
        }
    }


    // seed clusters of forest
    int fcc = 5 + rand() % 4;

    for (int i = 0; i < fcc; i++)
    {
        int choice = rand();
        if (choice % 2 == 7) {
            int cw = rand() % 5 + 3;
            int ch = rand() % 5 + 3;
            int tu = rand() % (width - cw);
            int tv = rand() % (height - ch);

            for (int u = tu; u < tu + cw; u++)
            {
                for (int v = tv; v < tv + ch; v++)
                {
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
        std::vector<std::vector<std::pair<int, int> > > neighbors = std::vector<std::vector<std::pair<int, int> > >(height);

        for (int v = 0; v < height; v++)
        {
            neighbors[v] = std::vector<std::pair<int, int> >(width);

            for (int u = 0; u < width; u++)
            {
                int right = (u + 1) % width;
                int up = (v + 1) % height;
                int down = std::max(v - 1, 0);
                int left = std::max(u - 1, 0);
                int d_incident = 0, f_incident = 0;

                if (board->getCell(right, v).getType() == BoardCell::TYPE::Desert)
                {
                    d_incident += 1;
                }
                else if (board->getCell(right, v).getType() == BoardCell::TYPE::Forest)
                {
                    f_incident += 1;
                }

                if (board->getCell(left, v).getType() == BoardCell::TYPE::Desert)
                {
                    d_incident += 1;
                }
                else if (board->getCell(left, v).getType() == BoardCell::TYPE::Forest)
                {
                    f_incident += 1;
                }

                if (board->getCell(u, up).getType() == BoardCell::TYPE::Desert)
                {
                    d_incident += 1;
                }
                else if (board->getCell(u, up).getType() == BoardCell::TYPE::Forest)
                {
                    f_incident += 1;
                }

                if (board->getCell(u, down).getType() == BoardCell::TYPE::Desert)
                {
                    d_incident += 1;
                }
                else if (board->getCell(u, down).getType() == BoardCell::TYPE::Forest)
                {
                    f_incident += 1;
                }

                neighbors[v][u] = std::make_pair(d_incident, f_incident);
            }
        }

        for (int v = 0; v < height; v++)
        {
            for (int u = 0; u < width; u++)
            {
                BoardCell cell = board->getCell(u, v);
                int d_count = neighbors[v][u].first;
                int f_count = neighbors[v][u].second;

                if (cell.getType() == BoardCell::TYPE::Desert)
                {
                    if (d_count == 1)
                    {
                        if (dis(gen) < 0)
                            board->setCell(u, v, PlainsCell());

                    }
                    else if (d_count == 0)
                    {
                        board->setCell(u, v, PlainsCell());
                    }
                }
                else if (cell.getType() == BoardCell::TYPE::Plains)
                {
                    if (d_count > 1)
                        board->setCell(u, v, DesertCell());
                    else if (d_count > 0 && dis(gen) > 0.5)
                    {
                        board->setCell(u, v, DesertCell());
                    }
                    else if (f_count > 1)
                    {
                        board->setCell(u, v, ForestCell());
                    }
                    else if (f_count > 0 && dis(gen) > 0.6)
                    {
                        board->setCell(u, v, ForestCell());
                    }

                }
                else if (cell.getType() == BoardCell::TYPE::Forest)
                {
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
}

void ClusterSeederV1::seedInfrastructure(GameState *state) {

}

void ClusterSeederV1::seedUnits(GameState *state) {
    for (int i = 0; i < 10; i++) {
        Civilian* civvie = new Civilian();
        civvie->setLocation(sf::Vector2i(rand() % state->getBoard()->getWidth(), rand() % state->getBoard()->getHeight()));
        state->units.push_back(civvie);
    }
}
