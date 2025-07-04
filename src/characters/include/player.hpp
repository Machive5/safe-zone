#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "character.hpp"

class Player: public Character {
    private:
        float frame_rate;
        float scaleX = 1;
        
    public:
        Animation run_animation;
        Animation idle_animation;
        Animation atk_animation;
        sf::Sprite sprite;
        float jump_force = 1000.0f;
        bool jump = false;
        
        Player(float frame_rate, float initPosX=0, float initPosY=0, int offsideX=0, int offsideY=0);

        void jumping(float gravityForce);
        void update();
        void idle();
        void moveRight();
        void moveLeft();
        void atk();
};
#endif