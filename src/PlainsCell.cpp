//
// Created by Nathan on 7/10/2015.
//

#include "PlainsCell.h"

PlainsCell::PlainsCell() {
    traversable = true;
    type = BoardCell::TYPE::Plains;
    baseColor = sf::Color(0, 222, 0);
}
