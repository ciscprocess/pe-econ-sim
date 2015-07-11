//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_BOARDCELL_H
#define PE_ECON_SIM_BOARDCELL_H


#include <SFML/Graphics.hpp>

class BoardCell {
public:
    BoardCell();
    enum TYPE { Plains, Desert, Forest, Water, Undef };

    TYPE getType() { return type; }

    const sf::Color &getBaseColor() const {
        return baseColor;
    }

protected:
    TYPE type;
    sf::Color baseColor;
};


#endif //PE_ECON_SIM_BOARDCELL_H
