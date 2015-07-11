//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_ISOMETRICSCENEVISUALIZER_H
#define PE_ECON_SIM_ISOMETRICSCENEVISUALIZER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "IsometricBoardVisualizer.h"

#include <utility>

using sf::Vector3f;
using sf::Transform;

class IsometricSceneVisualizer {
public:
    IsometricSceneVisualizer(Vector3f uBasis, Vector3f vBasis, sf::RenderTarget* target);

    void draw(GameState* state);
    sf::FloatRect getBounds() { return bounds; }

    void setInputPosition(sf::Vector2f vec) {
        inputEnabled = true;
        inputPosition = vec;
    };

    void removeInput() { inputEnabled = false; }

    Transform getTransform() { return Sux; }

    std::vector<std::pair<sf::Sprite, Unit*> > sprites;

private:
    Vector3f uBasis, vBasis;
    Transform Sux;
    IsometricBoardVisualizer boardVisualizer;
    sf::RenderTarget* target;
    sf::FloatRect bounds;

    bool inputEnabled = false;
    sf::Vector2f inputPosition;
};


#endif //PE_ECON_SIM_ISOMETRICSCENEVISUALIZER_H
