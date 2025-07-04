#include "include/player.hpp"

Player::Player(float frame_rate, float initPosX, float initPosY, int offsideX, int offsideY): Character("Emma", 1, 100, 10, 100) {
    this->frame_rate = frame_rate;

    this->run_animation = Animation("../assets/sprite/player", "run", false, 6, &this->sprite, this->frame_rate, 1.5f, offsideX, offsideY);
    this->idle_animation = Animation("../assets/sprite/player", "idle", false, 4, &this->sprite, this->frame_rate, 1.5f, offsideX, offsideY);
    this->atk_animation = Animation("../assets/sprite/player", "atk", false, 6, &this->sprite, this->frame_rate, 1.5f, offsideX, offsideY);
    this->boundingBox = sf::RectangleShape(sf::Vector2f(50, 65));
    
    scaleX = idle_animation.rescaleX;
    
    boundingBox.setOutlineColor(sf::Color::Red);
    boundingBox.setOutlineThickness(1);
    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2); 
    posX = initPosX;
    posY = initPosY;
}

void Player::jumping(float gravityForce){
    if (jump) {
        posY -= jump_force * frame_rate;
        jump_force -= gravityForce * frame_rate;
    }
    if (jump_force <= 0) {
        jump = false;
        jump_force = 1000.0f;
    }
}

void Player::update(){
    sprite.setPosition((posX), (posY));
    sprite.setScale(scaleX, run_animation.rescaleY);
    boundingBox.setPosition(posX, posY);
}

void Player::idle(){
    idle_animation.animate();
}

void Player::moveRight(){
    run_animation.animate(1);
    scaleX = run_animation.rescaleX;
}

void Player::moveLeft(){
    run_animation.animate(1);
    scaleX = -run_animation.rescaleX;
}

void Player::atk(){
    atk_animation.animate(1);
}