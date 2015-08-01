//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_TILESELECTEDEVENT_H
#define PE_ECON_SIM_TILESELECTEDEVENT_H

#include <SFML/System/Vector2.hpp>
#include "GameInteractionEvent.h"

namespace undocked {
namespace event {

    class ClickAtCoordinate : public GameInteractionEvent {
    public:
        ClickAtCoordinate(sf::Vector2f coordinates);

        sf::Vector2f coordinates;
    };

}
}


#endif //PE_ECON_SIM_TILESELECTEDEVENT_H
