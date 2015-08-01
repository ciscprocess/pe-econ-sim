//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_UNIT_H
#define PE_ECON_SIM_UNIT_H

#include <SFML/Graphics.hpp>

class Unit {
public:
    Unit() { }
    ~Unit();
    enum UnitType { Civilian, Military };
    UnitType getType() { return type; }
    sf::Vector2i getLocation() { return location; }
    sf::Vector2f getOffset() { return offset; }
    void setLocation(sf::Vector2i location) { this->location = location; }
    sf::Texture* getTexture() { return baseTexture; }
protected:
    UnitType type;
    sf::Texture* baseTexture;
    sf::Vector2i location;
    sf::Vector2f offset;
};


#endif //PE_ECON_SIM_UNIT_H
