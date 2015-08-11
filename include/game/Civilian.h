//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_CIVILIAN_H
#define PE_ECON_SIM_CIVILIAN_H

#include "Unit.h"

namespace undocked {
    namespace game {
        class Civilian : public Unit {
        public:
            Civilian();

            virtual double deathChance();
        };
    }
}

#endif //PE_ECON_SIM_CIVILIAN_H
