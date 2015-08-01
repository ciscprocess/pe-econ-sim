//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAMEINTERACTIONEVENT_H
#define PE_ECON_SIM_GAMEINTERACTIONEVENT_H


class GameInteractionEvent {
public:
    GameInteractionEvent() { }

    enum EventType { UnitSelected, TileSelected, ClickAtCoordinate};

    EventType getEventType() { return type; }
protected:
    EventType type;
};


#endif //PE_ECON_SIM_GAMEINTERACTIONEVENT_H
