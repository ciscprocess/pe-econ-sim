//
// Created by Nathan on 7/10/2015.
//

#include "ForestCell.h"

ForestCell::ForestCell() {
    traversable = false;
    type = BoardCell::TYPE::Forest;
    baseColor = sf::Color(0, 90, 0);
}
