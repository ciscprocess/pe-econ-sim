/*
 * file: ClusterSeederV2.h
 * author: Nathan Korzekwa
 * date: 2015-07-22
 * description:
 * the second, improved, terrain generator. it takes the model of ClusterSeederV1, but uses two, alternating rule sets
 * for cell propagation, and each cluster as a polar function associated with it that determines the relative rate of
 * growth for each tile surrounding it
 */

#ifndef PE_ECON_SIM_CLUSTERSEEDERV2_H
#define PE_ECON_SIM_CLUSTERSEEDERV2_H


#include "GameStateSeeder.h"

namespace undocked {
    namespace game {
        namespace generation {
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
                    sf::Vector2f location;
                private:
                    std::vector<std::pair<double, double>> sizesAndPhases;

                    // the generated polar function for a cluster
                    double func(double theta);
                    // the derivative of the logistic sigmoid
                    double dSigmoid(double x);

                };
            };
        }
    }
}




#endif //PE_ECON_SIM_CLUSTERSEEDERV1_H
