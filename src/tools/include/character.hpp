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
        
        int countFrames(const std::string& directory) {
            int count = 0;
            for (const auto& entry : std::filesystem::directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    count++;
                }
            }
            return count;
        }
        
    public: 
        float rescale = 1;
        Animation(std::string texture_dir="", std::string type="", bool individual = true, sf::Sprite* sprite=nullptr, float frame_rate=1, float resize=1){
            this->texture_directory = texture_dir;
            this->individual = individual;
            this->type = type;
            this->frame_rate = frame_rate;
            this->sprite = sprite;
            
            if (individual && type != "") {
                this->animation_frame = countFrames(texture_directory + "/" + type);
                textures.resize(animation_frame);
                for (int i = 0; i < animation_frame; i++) {
                    if (!textures[i].loadFromFile(texture_directory + "/" + type + "/" + std::to_string(i) + ".png")) {
                        throw std::runtime_error("Failed to load texture: " + texture_directory + "/" + type + "/" + std::to_string(i) + ".png");
                    }
                }

                sprite->setOrigin(textures[0].getSize().x / 2.f, textures[0].getSize().y / 2.f);
                rescale = (64.f / (float)textures[0].getSize().x) * resize;
            }
        }

        void animate(float animationPerSeccond = 1.0f){
            sprite->setTexture(textures[(int)state % animation_frame]);
            if (state >= animation_frame) {
                state = 0;
            }
            state += (frame_rate * animation_frame * animationPerSeccond);
        }
};

//------------------------------ creating character class ------------------------------

class Player: public Character {
    private:
        float frame_rate;
        Animation run_animation;
        Animation idle_animation;
        float scaleX = 1;
    
    public:
        sf::Sprite sprite;
        sf::RectangleShape boundingBox = sf::RectangleShape(sf::Vector2f(30, 70));

        Player(float frame_rate, float initPosX=0, float initPosY=0): Character("Emma", 1, 100, 10, 100) {
            this->frame_rate = frame_rate;
            this->run_animation = Animation("../assets/sprite/player", "run", true, &this->sprite, this->frame_rate, 2.0f);
            this->idle_animation = Animation("../assets/sprite/player", "idle", true, &this->sprite, this->frame_rate, 2.0f);

            scaleX = idle_animation.rescale;
            
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
            sprite.setScale(scaleX, run_animation.rescale);
            boundingBox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        }

        void idle(){
            idle_animation.animate();
            update();
        }

        void moveRight(){
            run_animation.animate(0.7);
            scaleX = run_animation.rescale;
            update();
        }

        void moveLeft(){
            run_animation.animate(0.7);
            scaleX = -run_animation.rescale;
            update();
        }
};

#endif