#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <cmath>
#include "tools/include/animation.hpp"

class Character { //this is base class for all characters
    public:
        std::string name;
        int level;
        int health;
        int atk;
        int speed;
        float jump_force = 0;

        float posX = 0;
        float posY = 0;

        sf::RectangleShape boundingBox;

        Character(std::string name, int level, int health, int atk, int speed) {
            this->name = name;
            this->level = level;
            this->health = health;
            this->atk = atk;
            this->speed = speed;
        }

        virtual void update() = 0; 
};

#endif