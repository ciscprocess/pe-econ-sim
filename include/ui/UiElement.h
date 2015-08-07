//
// Created by Nathan on 8/1/2015.
//

#ifndef PE_ECON_SIM_GUIELEMENT_H
#define PE_ECON_SIM_GUIELEMENT_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

namespace undocked {
    namespace ui {
        class UiElement {
        protected:
            UiElement(UiElement* parent, int x, int y, int w, int h);

        public:
            static std::map<std::string, std::function<sf::Vector2i(UiElement*)> > anchorPoints;
            virtual void draw(sf::RenderTarget&) = 0;
            void setAnchorPoint(std::function<sf::Vector2i(UiElement*)> anchor);

            sf::IntRect getArea() { return area;};
            UiElement* getParent() { return parent; }

        protected:
            sf::IntRect area;
            // a dynamically evaluated point that the "area" rect is relative to
            std::function<sf::Vector2i(UiElement*)> anchorPoint;
            UiElement* parent;
            std::vector<UiElement*> elements;
        };
    }
}

#endif //PE_ECON_SIM_GUIELEMENT_H
