#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>

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

class Animation { //this is tools for controlling animations
    private:
        std::string texture_directory;
        std::string type;
        std::vector<sf::Texture> textures;
        sf::Sprite* sprite;

        float frame_rate = 1;
        bool individual;
        int animation_frame = 0;
        float state = 0;
        
    public: 
        float rescaleX = 1;
        float rescaleY = 1;
        Animation(std::string texture_dir="", std::string type="", bool individual = true, int numberOfFrame=1, sf::Sprite* sprite=nullptr, float frame_rate=1, float resize=1){
            this->texture_directory = texture_dir;
            this->individual = individual;
            this->type = type;
            this->frame_rate = frame_rate;
            this->sprite = sprite;
            this->animation_frame = numberOfFrame;
            
            if (individual && type != "") {
                textures.resize(animation_frame);
                for (int i = 0; i < animation_frame; i++) {
                    if (!textures[i].loadFromFile(texture_directory + "/" + type + "/" + std::to_string(i) + ".png")) {
                        throw std::runtime_error("Failed to load texture: " + texture_directory + "/" + type + "/" + std::to_string(i) + ".png");
                    }
                }

                sprite->setOrigin(textures[0].getSize().x / 2.f, textures[0].getSize().y / 2.f);
                rescaleX = (64.f / (float)textures[0].getSize().x) * resize;
                rescaleY = (64.f / (float)textures[0].getSize().y) * resize;
            }
            else{
                if (type == "") {
                    return;
                }
                textures.resize(1);
                if (!textures[0].loadFromFile(texture_directory + "/" + type + ".png")) {
                    throw std::runtime_error("Failed to load texture: " + texture_directory + "/" + type + ".png");
                }
                sprite->setTexture(textures[0]);
                sprite->setOrigin((textures[0].getSize().x/animation_frame) / 2.f, textures[0].getSize().y / 2.f);
                rescaleX = (64.f / ((float)textures[0].getSize().x)/animation_frame) * resize;
                rescaleY = (64.f / (float)textures[0].getSize().y) * resize;
            }
        }

        void animate(float animationPerSeccond = 1.0f){
            if (individual){
                sprite->setTexture(textures[(int)state % animation_frame]);
                if (state >= animation_frame) {
                    state = 0;
                }
                state += (frame_rate * animation_frame * animationPerSeccond);
            }
            else{
                sprite->setTextureRect(sf::IntRect(
                    ((int)state % animation_frame) * (textures[0].getSize().x / animation_frame),
                    0,
                    (textures[0].getSize().x / animation_frame),
                    textures[0].getSize().y
                ));
                if (state >= animation_frame) {
                    state = 0;
                }
                state += (frame_rate * animation_frame * animationPerSeccond);
            }
        }
};

//------------------------------ creating character class ------------------------------

class Player: public Character {
    private:
        float frame_rate;
        Animation run_animation;
        Animation idle_animation;
        Animation atk_animation;
        Animation runAndGun_animation;

        float scaleX = 1;
    
    public:
        sf::Sprite sprite;
        
        Player(float frame_rate, float initPosX=0, float initPosY=0): Character("Emma", 1, 100, 10, 100) {
            this->frame_rate = frame_rate;
            
            this->run_animation = Animation("../assets/sprite/player", "run", true, 14, &this->sprite, this->frame_rate, 2.0f);
            this->idle_animation = Animation("../assets/sprite/player", "idle", true, 4, &this->sprite, this->frame_rate, 2.0f);
            this->atk_animation = Animation("../assets/sprite/player", "atk", true, 4, &this->sprite, this->frame_rate, 0.2f);
            this->runAndGun_animation = Animation("../assets/sprite/player", "run&gun", true, 6, &this->sprite, this->frame_rate, 0.2f);
            this->boundingBox = sf::RectangleShape(sf::Vector2f(30, 70));
            
            scaleX = idle_animation.rescaleX;
            
            boundingBox.setOutlineColor(sf::Color::Red);
            boundingBox.setOutlineThickness(1);
            boundingBox.setFillColor(sf::Color::Transparent);
            boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2); 
            posX = initPosX;
            posY = initPosY;
            update();
        }

        void update(){
            sprite.setPosition(posX, posY);
            sprite.setScale(scaleX, run_animation.rescaleY);
            boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        }

        void idle(){
            idle_animation.animate();
            update();
        }

        void moveRight(){
            run_animation.animate(0.7);
            scaleX = run_animation.rescaleX;
            update();
        }

        void moveLeft(){
            run_animation.animate(0.7);
            scaleX = -run_animation.rescaleX;
            update();
        }

        void runAndGunRight(){
            runAndGun_animation.animate(2.0);
            // scaleX = runAndGun_animation.rescale;
            update();
        }

        void runAndGunLeft(){
            runAndGun_animation.animate(2.5);
            // scaleX = -runAndGun_animation.rescale;
            update();
        } 

        void atk(){
            atk_animation.animate(2.5);
        }
};

class Zombie: public Character{
    private: 
        float frame_rate;
        Animation run_animation;
        Animation idle_animation;
        Animation atk_animation;
        Animation death_animation;
        Animation hurt_animation;

        float scaleX = 1;
    public:
        sf::Sprite sprite;
        Zombie(std::string name, std::string texture_dir, bool textureIndividual, float frame_rate, float initPosX=0, float initPosY=0): Character(name, 1, 100, 10, 100) {
            this->frame_rate = frame_rate;
            
            this->run_animation = Animation(texture_dir, "walk", textureIndividual, 10, &this->sprite, this->frame_rate, 2.0f);
            this->idle_animation = Animation(texture_dir, "idle", textureIndividual, 6, &this->sprite, this->frame_rate, 2.0f);
            this->atk_animation = Animation(texture_dir, "atk", textureIndividual, 5, &this->sprite, this->frame_rate, 0.2f);
            this->death_animation = Animation(texture_dir, "dead", textureIndividual, 5, &this->sprite, this->frame_rate, 0.2f);
            this->hurt_animation = Animation(texture_dir, "hurt", textureIndividual, 4, &this->sprite, this->frame_rate, 0.2f);
            this->boundingBox = sf::RectangleShape(sf::Vector2f(30, 70));

            scaleX = idle_animation.rescaleX;
            
            boundingBox.setOutlineColor(sf::Color::Red);
            boundingBox.setOutlineThickness(1);
            boundingBox.setFillColor(sf::Color::Transparent);
            boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2); 
            posX = initPosX;
            posY = initPosY;
            update();
        }

        void update(){
            sprite.setPosition(posX, posY);
            sprite.setScale(scaleX, run_animation.rescaleY);
            boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        }
};

class Zombie1: public Zombie {
    public:
        Zombie1(float frame_rate, float initPosX=0, float initPosY=0): Zombie("Zombie1", "../assets/sprite/zombie/Zombie_1", false, frame_rate, initPosX, initPosY) {
            update();
        }

        void update() override {
            Zombie::update();
        }
};



#endif