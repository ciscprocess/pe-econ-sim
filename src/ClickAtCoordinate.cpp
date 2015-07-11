//
// Created by Nathan on 7/10/2015.
//

#include "ClickAtCoordinate.h"

ClickAtCoordinate::ClickAtCoordinate(sf::Vector2f coordinates) : coordinates(coordinates) {
    this->type = GameInteractionEvent::ClickAtCoordinate;
}
