//
// Created by Nathan on 7/10/2015.
//

#include "world/DesertCell.h"

namespace undocked {
    namespace world {
        DesertCell::DesertCell() {
            traversable = true;
            type = BoardCell::TYPE::Desert;
            baseColor = sf::Color(244, 244, 0);
        }
    }
}