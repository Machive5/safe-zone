#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <iostream>

#include "character.hpp"

class Scene {
    protected:
        sf::RenderWindow* window;
        Player* player;
        sf::Texture groundTexture;
        std::vector<sf::Texture> layerTextures;

        bool isGrounded = false;
        bool isJumping = false;

        float gravityForce;
        float frame_rate;

        void gravity() {
            sf::FloatRect playerBounds = player->boundingBox.getGlobalBounds();
            sf::FloatRect groundBounds = groundBoundingBox.getGlobalBounds();
            isGrounded = playerBounds.intersects(groundBounds);

            if (!isGrounded || isJumping) {

                //for jump effect
                player->jump_force -= gravityForce * frame_rate;
                if (player->jump_force < 0) {
                    player->jump_force = 0;
                }
                player->posY += (gravityForce - player->jump_force) * frame_rate;
                player->update();

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
        char keyEvent = '\0'; // Using char for single key events, can be extended to string if needed
        char horizDir = '\0'; // 'A' for left, 'D' for right
        char vertDir = '\0'; // 'W' for up, 'S' for down

        sf::RectangleShape groundBoundingBox = sf::RectangleShape(sf::Vector2f(5000, 70)); // Assuming the ground covers the whole window
        sf::Sprite ground;
        std::vector<sf::Sprite> layerSprite;

        Scene(sf::RenderWindow* window, Player* player, float frame_rate = (1.0f / 60.0f), float gravity_force = 500.0f, std::string groundFile="", std::string directory="", std::string layerFiles=""){
            this->window = window;
            this->player = player;
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

        virtual void update() = 0;
};


class Scene1: public Scene {
    public:

        Scene1(sf::RenderWindow* window, Player* player, float frame_rate = (1.0f / 60.0f), std::string groundFile="", std::string directory="", std::string layerFiles="")
        :Scene(window, player, frame_rate, 500.0f, groundFile, directory, layerFiles) {
            
            groundBoundingBox.setOrigin(0,groundBoundingBox.getSize().y);
            groundBoundingBox.setFillColor(sf::Color::Transparent);
            groundBoundingBox.setOutlineColor(sf::Color::Blue);
            groundBoundingBox.setOutlineThickness(3);
            groundBoundingBox.setPosition(0, window->getSize().y);

            printf("scene loaded\n");

        }

        void update() {
            gravity();
            player->idle();
            
            switch (horizDir) {
                case 'A':
                    player->posX -= player->speed * frame_rate;
                    if (player->posX < 100) {
                        player->posX = 100; // Prevent going out of bounds

                        float moveX = player->speed * frame_rate;
                        moveX = safeEdgeX(moveX, ground);
                        ground.move(moveX,0);
                        groundBoundingBox.setPosition(ground.getPosition().x, groundBoundingBox.getPosition().y);
                        
                        for (unsigned long i = 0; i < layerSprite.size(); i++) {
                            if (moveX == 0) {
                                continue; // No movement needed
                            }

                            moveX = (player->speed / ((i+1)/0.5)) * frame_rate;
                            layerSprite[i].move(safeEdgeX(moveX,layerSprite[i]), 0);
                        }

                    }

                    player->moveLeft();
                    break;

                case 'D':
                    player->posX += player->speed * frame_rate;
                    if (player->posX > window->getSize().x - 100) {
                        player->posX = window->getSize().x - 100; // Prevent going out of bounds

                        float moveX = -(player->speed * frame_rate);
                        moveX = safeEdgeX(moveX, ground);
                        ground.move(moveX,0);
                        groundBoundingBox.setPosition(ground.getPosition().x, groundBoundingBox.getPosition().y);
                        
                        for (unsigned long i = 0; i < layerSprite.size(); i++) {
                            if (moveX == 0) {
                                continue; // No movement needed
                            }
                            moveX = -(player->speed / ((i+1)/0.8) * frame_rate);
                            layerSprite[i].move(safeEdgeX(moveX,layerSprite[i]), 0);
                        }

                    }
                    player->moveRight();
                    break;
            }

            switch (vertDir){
                case 'W':
                    if (isGrounded) {
                        player->jump_force = 800.0f;
                        isJumping = true;
                    }
                    break;
            }

            player->update();
            
            window->clear(sf::Color(30, 53, 59));

            for (unsigned long i = layerSprite.size(); i > 0; i--) {
                window->draw(layerSprite[i-1]);
            }
            window->draw(ground);
            window->draw(groundBoundingBox);
            window->draw(player->sprite);
            window->draw(player->boundingBox);
        }
};

#endif