#include "include/normalZombie.hpp"

NormalZombie::NormalZombie(float frame_rate, float initPosX, float initPosY, Player* player): Zombie("Zombie1", "../assets/sprite/zombie/Zombie_1", false, frame_rate, initPosX, initPosY) {
    this->player = player;
    speed = 50; 
    update();
}

void NormalZombie::update() {
    // printf("state %d\n", state);
    switch (state)
    {
        case 0: // idle
            if (counter <= 0){
                randomIdle = (rand()%3);
                counter = 1;
            }

            if (std::abs(player->posX - posX) < 200) {
                state = 1; // switch to run if player is far away
                counter = 0; // reset counter
            }

            if (randomIdle == 1.0f){
                moveRight();
            }else if(randomIdle == 2.0f){
                moveLeft();
            }
            else {
                idle_animation.animate();
            }
            counter -= frame_rate; 
            break;

        case 1: // run
            if (std::abs(player->posX - posX) > 200) {
                state = 0; // switch to idle if player is close
            }

            if (std::abs(player->posX - posX) < 20){
                state = 2;
            }

            if (player->posX > posX) {
                moveRight();
            } else {
                moveLeft();
            }
            break;

        case 2: // atk
            atk();
            if (atk_animation.status == true) {
                state = 3;
            }
            break;
        case 3:
            hurt_animation.animate(2);
            if (hurt_animation.status == true) {
                state = 99; // switch to death state
            }
            break;
        case 99:
            death();
            break;

        default:
            break;
    }

    Zombie::update();
}

void NormalZombie::moveRight() {
    posX += speed * frame_rate;
    run_animation.animate(1);
    scaleX = run_animation.rescaleX;
}

void NormalZombie::moveLeft() {
    posX -= speed * frame_rate;
    run_animation.animate(1);
    scaleX = -run_animation.rescaleX;
}

void NormalZombie::atk() {
    atk_animation.animate(1.6);
}

void NormalZombie::death() {
    death_animation.animate(1);
    if (death_animation.status == true && state == 99) {
        printf("isDead %d\n", death_animation.status);
        isDead = true;
    }
}