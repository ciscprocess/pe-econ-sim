//
// Created by Nathan on 7/10/2015.
//

#include "game/Unit.h"

namespace undocked {
    namespace game {
        Unit::~Unit() {
            delete baseTexture;
        }
    }
}