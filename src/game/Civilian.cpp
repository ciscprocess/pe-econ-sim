//
// Created by Nathan on 7/10/2015.
//

#include "game/Civilian.h"

namespace undocked {
    namespace game {
        Civilian::Civilian() {
            type = Unit::UnitType::Civilian;
            baseTexture = new sf::Texture();
            baseTexture->loadFromFile("./data/civilian.png");
            offset.x = 1.5f;
            offset.y = -1.1f;
        }
    }
}