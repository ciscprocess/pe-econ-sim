//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_CLUSTERSEEDERV1_H
#define PE_ECON_SIM_CLUSTERSEEDERV1_H


#include "GameStateSeeder.h"

class ClusterSeederV1 : public GameStateSeeder {
public:
    ClusterSeederV1();
    ~ClusterSeederV1();

    virtual void seedTerrain(GameState *state);
    virtual void seedInfrastructure(GameState *state);
    virtual void seedUnits(GameState *state);
};


#endif //PE_ECON_SIM_CLUSTERSEEDERV1_H
