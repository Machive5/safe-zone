#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__

#include "character.hpp"

class Zombie: public Character{
    public:
        float frame_rate;   
        float scaleX = 1;
        bool isDead = false;
        
        sf::Sprite sprite;

        Animation run_animation;
        Animation idle_animation;
        Animation atk_animation;
        Animation death_animation;
        Animation hurt_animation;

        Zombie(std::string name, std::string texture_dir, bool textureIndividual, float frame_rate, float initPosX=0, float initPosY=0): Character(name, 1, 100, 10, 100) {
            this->frame_rate = frame_rate;
            
            this->run_animation = Animation(texture_dir, "walk", textureIndividual, 10, &this->sprite, this->frame_rate, 2.3f);
            this->idle_animation = Animation(texture_dir, "idle", textureIndividual, 6, &this->sprite, this->frame_rate, 2.3f);
            this->atk_animation = Animation(texture_dir, "atk", textureIndividual, 5, &this->sprite, this->frame_rate, 2.3f);
            this->death_animation = Animation(texture_dir, "dead", textureIndividual, 5, &this->sprite, this->frame_rate, 2.3f);
            this->hurt_animation = Animation(texture_dir, "hurt", textureIndividual, 4, &this->sprite, this->frame_rate, 2.3f);
            this->boundingBox = sf::RectangleShape(sf::Vector2f(40, 70));

            scaleX = idle_animation.rescaleX;
            
            boundingBox.setOutlineColor(sf::Color::Red);
            boundingBox.setOutlineThickness(1);
            boundingBox.setFillColor(sf::Color::Transparent);
            boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2); 
            posX = initPosX;
            posY = initPosY;
        }

        void update(){
            sprite.setPosition(posX, posY);
            sprite.setScale(scaleX, run_animation.rescaleY);
            boundingBox.setPosition(posX, posY);
        }

        virtual void death() = 0;
};
#endif