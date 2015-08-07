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

        class IsometricBoardVisualizer : public sf::Drawable {
        public:
            IsometricBoardVisualizer(sf::Vector2f uBasis, sf::Vector2f vBasis);
            void update(CellularBoard* board);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        private:
            Transform Sux;
            sf::RenderTexture target;
            uint32_t width;
            uint32_t height;

            sf::Vector2f offset;
        };
    }
}

#endif //PE_ECON_SIM_ISOMETRICBOARDVISUALIZER_H
