//
// Created by Nathan on 8/1/2015.
//

#include <ui/MessageBox.h>
#include "ui/UiManager.h"

namespace undocked {
    namespace ui {
        UiManager::UiManager(int width, int height) : UiElement(nullptr, 0, 0, width, height) {
        }

        UiManager::~UiManager() {
            // release memory
            for (auto element : elements) {
                delete element;
            }
        }

        void UiManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
            for (auto element : elements) {
                target.draw(*element);
            }
        }

        void UiManager::addElement(UiElement *element) {
            elements.push_back(element);
        }

        UiElement* UiManager::createMessageBox(int x, int y, int w, int h, std::string message) {
            auto box = new MessageBox(this, x, y, w, h, message);
            addElement(box);
            return box;
        }

        void UiManager::updateSize(int width, int height) {
            this->area.width = width;
            this->area.height = height;
        }
    }
}

