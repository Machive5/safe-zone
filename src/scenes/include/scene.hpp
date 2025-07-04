#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>

#include "characters/include/character.hpp"
#include "system/include/State.h"


// base class for all scenes that needs paralax effect
class Scene {
    protected:
        sf::RenderWindow* window;
        sf::Texture groundTexture;
        std::vector<sf::Texture> layerTextures;

        sf::RectangleShape groundBoundingBox = sf::RectangleShape(sf::Vector2f(5000, 70));
        sf::Sprite ground;
        std::vector<sf::Sprite> layerSprite;

        float gravityForce;
        float frame_rate;

        void gravity(Character* character, bool jump = false);
        float safeEdgeX(float moveX, sf::Sprite sprite);
    
    public:
        int layerSize = 0;
        char keyEvent = '\0'; 
        char horizDir = '\0'; 
        char vertDir = '\0';

        Scene(sf::RenderWindow* window, float frame_rate = (1.0f / 60.0f), float gravity_force = 500.0f, std::string groundFile="", std::string directory="", std::string layerFiles="");
};

#endif