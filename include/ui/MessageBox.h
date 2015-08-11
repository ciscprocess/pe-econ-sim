//
// Created by Nathan on 8/1/2015.
//

#ifndef PE_ECON_SIM_MESSAGEBOX_H
#define PE_ECON_SIM_MESSAGEBOX_H

#include "UiElement.h"

namespace undocked {
    namespace ui {
        class MessageBox : public UiElement {
        public:
            MessageBox(UiElement *parent, int x, int y, int w, int h, std::string m) : UiElement(parent, x, y, w, h),
                                                                                       message(m) {}
            void draw(sf::RenderTarget&, sf::RenderStates states) const;
            void setMessage(std::string message) { this->message = message; };

        private:
            std::string message;
        };
    }
}

#endif //PE_ECON_SIM_MESSAGEBOX_H
