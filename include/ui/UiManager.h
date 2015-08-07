//
// Created by Nathan on 8/1/2015.
//

#ifndef PE_ECON_SIM_UIMANAGER_H
#define PE_ECON_SIM_UIMANAGER_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "UiElement.h"

namespace undocked {
    namespace ui {
        class UiManager : public UiElement {
        public:
            UiManager(int width, int height);
            ~UiManager();
            void draw(sf::RenderTarget&);
            void addElement(UiElement*);
            UiElement* createMessageBox(int x, int y, int w, int h, std::string message);
            void updateSize(int width, int height);

        private:
            sf::RenderTexture buffer;
        };
    }
}

#endif //PE_ECON_SIM_UIMANAGER_H
