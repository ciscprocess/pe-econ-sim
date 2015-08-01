//
// Created by Nathan on 7/10/2015.
//

#include "event/ClickAtCoordinate.h"

ClickAtCoordinate::ClickAtCoordinate(sf::Vector2f coordinates) : coordinates(coordinates) {
    this->type = GameInteractionEvent::ClickAtCoordinate;
}
