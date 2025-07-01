#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>

#include "character.hpp"
#include "../../system/include/State.h"


// base class for all scenes that needs paralax effect
class Scene {
    protected:
        sf::RenderWindow* window;
        sf::Texture groundTexture;
        std::vector<sf::Texture> layerTextures;

        bool isGrounded = false;
        bool isJumping = false;

        float gravityForce;
        float frame_rate;

        void gravity(Character* character, bool jump = false) {
            sf::FloatRect playerBounds = character->boundingBox.getGlobalBounds();
            sf::FloatRect groundBounds = groundBoundingBox.getGlobalBounds();
            isGrounded = playerBounds.intersects(groundBounds);
            
            if ((!isGrounded || isJumping)) {
                
                float finalForce = gravityForce;
                //for jump effect
                
                if (jump){
                    character->jump_force -= gravityForce * frame_rate;
                    if (character->jump_force < 0) {
                        character->jump_force = 0;
                    }

                    finalForce = gravityForce - character->jump_force;
                }

                character->posY += finalForce * frame_rate;

                character->update();

                isJumping = false;
            }
        }

        float safeEdgeX(float moveX, sf::Sprite sprite) {
            if (moveX > 0 && sprite.getPosition().x + moveX > 0)
                return 0 - sprite.getPosition().x;

            if (moveX < 0 && sprite.getPosition().x + sprite.getGlobalBounds().width + moveX < window->getSize().x)
                return window->getSize().x - (sprite.getPosition().x + sprite.getGlobalBounds().width);
            
            return moveX;
        }
    
    public:
        int layerSize = 0;
        char keyEvent = '\0'; 
        char horizDir = '\0'; 
        char vertDir = '\0';

        sf::RectangleShape groundBoundingBox = sf::RectangleShape(sf::Vector2f(5000, 70)); // Assuming the ground covers the whole window
        sf::Sprite ground;
        std::vector<sf::Sprite> layerSprite;

        Scene(sf::RenderWindow* window, float frame_rate = (1.0f / 60.0f), float gravity_force = 500.0f, std::string groundFile="", std::string directory="", std::string layerFiles=""){
            this->window = window;
            this->frame_rate = frame_rate;
            this->gravityForce = gravity_force;

            layerSize = -1;

            if (groundFile != "" && !groundTexture.loadFromFile(groundFile)) {
                throw std::runtime_error("Failed to load ground texture");
            }
            ground.setTexture(groundTexture);

            if (layerFiles != ""){
                for (const auto& entry : std::filesystem::directory_iterator(directory)) {
                    if (entry.is_regular_file()) {
                        layerSize += 1;
                    }
                }
            }

            if (layerSize >= 0) {
                layerTextures.resize(layerSize);
                layerSprite.resize(layerSize);
                for (int i = 1; i <= layerSize; i++) {
                    if (!layerTextures[i].loadFromFile(directory + layerFiles + std::to_string(i) + ".png")) {
                        throw std::runtime_error("Failed to load layer texture: " + directory + layerFiles + std::to_string(i) + ".png");
                    }

                    layerSprite[(i-1)].setTexture(layerTextures[(i-1)]);
                    // layerSprite[(i-1)].setFillColor(sf::Color(255, 255, 255, 128)); // Set transparency
                }
            }
        }
};

#endif