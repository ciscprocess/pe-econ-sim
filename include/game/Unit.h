//
// Created by Nathan on 7/10/2015.
//

#ifndef PE_ECON_SIM_UNIT_H
#define PE_ECON_SIM_UNIT_H

#include <SFML/Graphics.hpp>

namespace undocked {
    namespace game {
        class Unit {
        public:
            Unit() { }
            ~Unit();
            enum UnitType { Civilian, Military };

            UnitType getType() { return type; }
            sf::Vector2i getLocation() { return location; }
            sf::Vector2f getOffset() { return offset; }
            void setLocation(sf::Vector2i location) { this->location = location; }
            sf::Texture* getTexture() { return baseTexture; }
            virtual double deathChance() = 0;
            uint32_t getHealth() const {
                return health;
            }

            uint32_t getAge() const {
                return age;
            }

            void tick() {
                age++;
                health--;
            };
        protected:
            UnitType type;
            sf::Texture* baseTexture;
            sf::Vector2i location;
            sf::Vector2f offset;

        protected:
            uint32_t health = 0;
            uint32_t age = 0;
        };
    }
}

#endif //PE_ECON_SIM_UNIT_H
