//
// Created by Nathan on 7/10/2015.
//

#include "world/PlainsCell.h"

namespace undocked {
    namespace world {
        PlainsCell::PlainsCell() {
            traversable = true;
            type = BoardCell::TYPE::Plains;
            baseColor = sf::Color(0, 222, 0);
        }
    }
}