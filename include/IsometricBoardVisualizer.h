//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
#define PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
#include <SFML/Graphics.hpp>

#include <SFML/System.hpp>
#include "GameState.h"

using sf::Transform;

class IsometricBoardVisualizer {
public:
    IsometricBoardVisualizer(Transform& sux, sf::RenderTarget* target);
    void draw(CellularBoard* board, sf::Vector2f* input = nullptr);

    const sf::FloatRect &getViewport() const {
        return viewport;
    }

private:
    Transform Sux;
    sf::RenderTarget* target;
    sf::FloatRect viewport;
};


#endif //PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
