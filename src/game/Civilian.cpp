//
// Created by Nathan on 7/10/2015.
//

#include <numeric/Random.h>
#include "game/Civilian.h"

namespace undocked {
    namespace game {
        numeric::Random random;

        Civilian::Civilian() {
            type = Unit::UnitType::Civilian;
            baseTexture = new sf::Texture();
            baseTexture->loadFromFile("./data/civilian.png");
            offset.x = 1.5f;
            offset.y = -1.1f;

            random.setUniform(10, 25);
            age = (uint32_t) random.getUniformInteger();
            health = (uint32_t) random.getUniformInteger() + 20000;
        }

        double Civilian::deathChance() {
            return health > 0 ? std::min(1., age / 13000000.) : 1;
        }
    }
}