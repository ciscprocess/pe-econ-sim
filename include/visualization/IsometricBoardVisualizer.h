//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
#define PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
#include <SFML/Graphics.hpp>

#include <SFML/System.hpp>
#include "game/GameState.h"

namespace undocked {
    namespace visualization {
        using sf::Transform;
        using world::CellularBoard;

        class IsometricBoardVisualizer {
        public:
            IsometricBoardVisualizer(Transform& sux, sf::RenderTarget* target);
            void draw(CellularBoard* board, sf::Vector2f* input = nullptr);

        private:
            Transform Sux;
            sf::RenderTarget* target;
        };
    }
}

#endif //PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
