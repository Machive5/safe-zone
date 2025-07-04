#include "include/flyingZombie.hpp"

FlyingZombie::FlyingZombie(float frame_rate, float initPosX, float initPosY, Player* player): Zombie("FlyingZombie", "", false, frame_rate, initPosX, initPosY) {
    this->frame_rate = frame_rate;
    
    this->run_animation = Animation("../assets/sprite/zombie/Zombie_5", "walk", false, 7, &this->sprite, this->frame_rate, 1.0f);
    this->idle_animation = Animation("../assets/sprite/zombie/Zombie_5", "idle", false, 9, &this->sprite, this->frame_rate, 1.0f);
    this->death_animation = Animation("../assets/sprite/zombie/Zombie_5", "dead", false, 9, &this->sprite, this->frame_rate, 1.0f);
    this->boundingBox = sf::RectangleShape(sf::Vector2f(20, 50));

    boundingBox.setOutlineColor(sf::Color::Red);
    boundingBox.setOutlineThickness(1);
    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2); 

    this->player = player;
    posY = 300;
    speed = 50; 
    update();
}

void FlyingZombie::update(){
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
            speed = 200;

            if (std::abs(player->posX - posX) > 400) {
                state = 0; // switch to idle if player is far
            }

            if (boundingBox.getGlobalBounds().intersects(player->boundingBox.getGlobalBounds())) {
                state = 99; // switch to death state if colliding with player
            }

            if (player->posX > posX) {
                posX += speed * frame_rate;
                sprite.setRotation(atan2(player->posY - posY, -player->posX + posX) * 180 / 3.14159f);
                posY -= speed*-sin((sprite.getRotation())*3.14159f/180) * frame_rate;
                run();
                scaleX = run_animation.rescaleX;
            } else {
                posX -= speed * frame_rate;
                sprite.setRotation(-atan2(player->posY - posY, -player->posX + posX) * 180 / 3.14159f);
                posY += speed*-sin((sprite.getRotation())*3.14159f/180) * frame_rate;
                run();
                scaleX = -run_animation.rescaleX;
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

void FlyingZombie::moveRight() {
    posX += speed * frame_rate;
    idle_animation.animate(1);
    scaleX = idle_animation.rescaleX;
}

void FlyingZombie::moveLeft() {
    posX -= speed * frame_rate;
    idle_animation.animate(1);
    scaleX = -idle_animation.rescaleX;
}

void FlyingZombie::run(){
    if (run_animation.state == 3){
        return;
    }
    run_animation.animate(1);
}

void FlyingZombie::death() {
    death_animation.animate(1);
    if (death_animation.status == true && state == 99) {
        printf("isDead %d\n", death_animation.status);
        isDead = true;
    }
}