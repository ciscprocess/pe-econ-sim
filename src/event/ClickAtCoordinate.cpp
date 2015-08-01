//
// Created by Nathan on 7/10/2015.
//

#include "event/ClickAtCoordinate.h"

namespace undocked {
    namespace event {
        ClickAtCoordinate::ClickAtCoordinate(sf::Vector2f coordinates) : coordinates(coordinates) {
            this->type = GameInteractionEvent::ClickAtCoordinate;
        }
    }
}