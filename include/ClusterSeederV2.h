//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_CLUSTERSEEDERV2_H
#define PE_ECON_SIM_CLUSTERSEEDERV2_H


#include "GameStateSeeder.h"

class ClusterSeederV2 : public GameStateSeeder {
public:
    ClusterSeederV2();
    ~ClusterSeederV2();

    virtual void seedTerrain(GameState *state);
    virtual void seedInfrastructure(GameState *state);
    virtual void seedUnits(GameState *state);

    class AnchorPoint {
    public:
       AnchorPoint(sf::Vector2f);
        double getComponent(sf::Vector2f point);
    private:
        double maximumComponent;
        sf::Vector2f location;
        std::vector<std::pair<double, double>> sizesAndPhases;

        double func(double theta);
        double dSigmoid(double x);

    };
};


#endif //PE_ECON_SIM_CLUSTERSEEDERV1_H
