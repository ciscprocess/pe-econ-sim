//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_ISOMETRICSCENEVISUALIZER_H
#define PE_ECON_SIM_ISOMETRICSCENEVISUALIZER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "IsometricBoardVisualizer.h"

#include <utility>


namespace undocked {
    namespace visualization {
        using game::GameState;
        using game::Unit;

        class IsometricSceneVisualizer : public sf::Drawable {
        public:
            IsometricSceneVisualizer(sf::Vector2f uBasis, sf::Vector2f vBasis);

            void update(GameState* state);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            void setInputPosition(sf::Vector2f vec) {
                inputEnabled = true;
                inputPosition = vec;
            };

            void removeInput() { inputEnabled = false; }

            Transform getTransform() { return Sux; }

            std::vector<std::pair<sf::Sprite, Unit*> > sprites;

            Unit* findUnitAtLocation(sf::Vector2f);

            game::GameState* state;

        private:
            Transform Sux;
            Transform Sxu;

            bool inputEnabled = false;
            sf::Vector2f inputPosition;
        };
    }
}

using sf::Transform;


#endif //PE_ECON_SIM_ISOMETRICSCENEVISUALIZER_H
