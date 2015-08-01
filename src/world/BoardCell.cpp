//
// Created by Nathan on 7/10/2015.
//

#include "world/BoardCell.h"

namespace undocked {
    namespace world {
        BoardCell::BoardCell(sf::Color baseColor) :
                baseColor(baseColor),
                traversable(true) {
            type = TYPE::Undef;
        }
    }
}
