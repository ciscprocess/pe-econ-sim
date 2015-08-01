//
// Created by Nathan on 7/10/2015.
//

#include "world/ForestCell.h"

namespace undocked {
    namespace world {
        ForestCell::ForestCell() {
            traversable = true;
            type = BoardCell::TYPE::Forest;
            baseColor = sf::Color(0, 90, 0);
        }
    }
}