#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>

class Animation { //this is tools for controlling animations
    private:
        std::string texture_directory;
        std::string type;
        std::vector<sf::Texture> textures;
        sf::Sprite* sprite;

        float frame_rate = 1;
        bool individual;
        int animation_frame = 0;
        int dimension[2] = {0,0};
        
    public: 
        float rescaleX = 1;
        float rescaleY = 1;
        bool status = true;
        float state = 0;
        
        Animation(std::string texture_dir="", std::string type="", bool individual = true, int numberOfFrame=1, sf::Sprite* sprite=nullptr, float frame_rate=1, float resize=1, int offsideX = 0, int offsideY = 0);

        ~Animation(){
            textures.clear();
        }
        void animate(float animationPerSeccond = 1.0f);
};

#endif // ANIMATION_HPP