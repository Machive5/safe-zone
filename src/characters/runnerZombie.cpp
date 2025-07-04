#include "include/runnerZombie.hpp"

RunnerZombie::RunnerZombie(float frame_rate, float initPosX, float initPosY, Player* player): Zombie("Zombie1", "../assets/sprite/zombie/Zombie_2", false, frame_rate, initPosX, initPosY) {
    this->player = player;
    speed = 50; 
    update();
}

void RunnerZombie::update(){
    // printf("state %d\n", state);
    switch (state)
    {
        case 0: // idle
            if (counter <= 0){
                randomIdle = (rand()%3);
                counter = 1;
            }

            if (std::abs(player->posX - posX) < 400) {
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
            speed = 90;

            if (std::abs(player->posX - posX) > 400) {
                state = 0; // switch to idle if player is close
            }

            if (std::abs(player->posX - posX) < 20){
                state = 2;
                speed = 50; 
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
                state = 99;
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

void RunnerZombie::moveRight() {
    posX += speed * frame_rate;
    run_animation.animate(1);
    scaleX = run_animation.rescaleX;
}

void RunnerZombie::moveLeft() {
    posX -= speed * frame_rate;
    run_animation.animate(1);
    scaleX = -run_animation.rescaleX;
}

void RunnerZombie::atk() {
    atk_animation.animate(1.6);
}

void RunnerZombie::death(){
    death_animation.animate(1);
    if (death_animation.status == true && state == 99) {
        printf("isDead %d\n", death_animation.status);
        isDead = true;
    }
}