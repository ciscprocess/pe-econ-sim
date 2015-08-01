//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAME_H
#define PE_ECON_SIM_GAME_H

#include "game/GameState.h"
#include "visualization/IsometricSceneVisualizer.h"
#include "event/GameInteractionEvent.h"

namespace undocked {
    namespace game {
        using visualization::IsometricSceneVisualizer;

        class Game {
        public:
            Game(sf::RenderTarget* display);
            bool run();

            void nativeEventHandler(sf::Event);

        private:
            GameState* state;
            IsometricSceneVisualizer* visualizer;
            sf::RenderTarget* target;
            sf::View gameView;
            sf::Vector2i mouseStart;
            sf::Vector2i mapStart;

            bool middleButtonDown = false;
        };
    }
}

#endif //PE_ECON_SIM_GAME_H
