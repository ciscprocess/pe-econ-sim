//
// Created by Nathan on 8/1/2015.
//

#include "ui/UiElement.h"

namespace undocked {
    namespace ui {

        std::map<std::string, std::function<sf::Vector2i(UiElement*)> > UiElement::anchorPoints = {
                {"BOTTOM_LEFT", [](UiElement* el) {
                    int x = el->getParent()->getArea().left;
                    int y = el->getParent()->getArea().top + el->getParent()->getArea().height - 1;
                    return sf::Vector2i(x, y);
                }}
        };

        UiElement::UiElement(UiElement* parent, int x, int y, int w, int h) : area(x, y, w, h),
                                                                              parent(parent) {
            anchorPoint = [](UiElement*) { return sf::Vector2i(0,0); };
        }

        void UiElement::setAnchorPoint(std::function<sf::Vector2i(UiElement *)> anchor) {
            this->anchorPoint = anchor;
        }
    }
}
