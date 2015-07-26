//
// Created by Nathan on 7/10/2015.
//

#include "DesertCell.h"

DesertCell::DesertCell() {
    traversable = true;
    type = BoardCell::TYPE::Desert;
    baseColor = sf::Color(244, 244, 0);
}
