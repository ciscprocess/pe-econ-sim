//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_GAME_H
#define PE_ECON_SIM_GAME_H

#include <ui/UiManager.h>
#include <ui/MessageBox.h>
#include "game/GameState.h"
#include "visualization/IsometricSceneVisualizer.h"
#include "event/GameInteractionEvent.h"

namespace undocked {
    namespace game {
        using visualization::IsometricSceneVisualizer;
        using visualization::IsometricBoardVisualizer;

        class Game : public sf::Drawable {
        public:
            Game(uint32_t width, uint32_t height);

            bool run();

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            void nativeEventHandler(sf::Event);

        private:
            GameState* state;
            IsometricSceneVisualizer visualizer;
            IsometricBoardVisualizer boardVisualizer;
            sf::RenderTexture target;
            sf::RenderTexture uiTarget;
            sf::View gameView;
            sf::Vector2i mouseStart;
            sf::Vector2i mapStart;
            ui::UiManager uiManager;
            ui::MessageBox* box;

            bool middleButtonDown = false;
        };
    }
}

#endif //PE_ECON_SIM_GAME_H
