//
// Created by Nathan on 7/10/2015.
//

#include "BoardCell.h"

BoardCell::BoardCell(sf::Color baseColor) :
        baseColor(baseColor),
        traversable(true) {
    type = TYPE::Undef;
}
