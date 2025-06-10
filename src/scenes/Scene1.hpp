#ifndef SCENE1_HPP
#define SCENE1_HPP

#include "../system/include/State.h"
#include "../tools/include/scene.hpp"

class Scene1: public Scene, public State {
    private:
        Player* player;

        // Directional keys
        char horizDir = '\0'; // 'A' for left, 'D' for right
        char vertDir = '\0'; // 'W' for up, 'S' for down

        // Gravity force
        const float gravityForce = 980.0f; // Adjust as needed for your game physics

    public:

        Scene1(sf::RenderWindow* window, float frame_rate = (1.0f / 60.0f), std::string groundFile="", std::string directory="", std::string layerFiles="")
        :Scene(window, frame_rate, 500.0f, groundFile, directory, layerFiles) {
            player = new Player(frame_rate, 100, window->getSize().y - 100);
            groundBoundingBox.setOrigin(0,groundBoundingBox.getSize().y);
            groundBoundingBox.setFillColor(sf::Color::Transparent);
            groundBoundingBox.setOutlineColor(sf::Color::Blue);
            groundBoundingBox.setOutlineThickness(3);
            groundBoundingBox.setPosition(0, window->getSize().y);

            printf("scene loaded\n");

        }

        void update() override {
            gravity(player, true);
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
        }

        void render(sf::RenderTarget & target) override {
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

        void handle_event(sf::Event event) override {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::A:
                        horizDir = 'A';
                        break;
                    case sf::Keyboard::D:
                        horizDir = 'D';
                        break;
                    case sf::Keyboard::W:
                        vertDir = 'W';
                        break;
                    case sf::Keyboard::S:
                        vertDir = 'S';
                        break;
                    default:
                        break;
                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::A:
                    case sf::Keyboard::D:
                        horizDir = '\0';
                        break;
                    case sf::Keyboard::W:
                    case sf::Keyboard::S:
                        vertDir = '\0';
                        break;
                    default:
                        break;
                }
            }
        }

        int get_next_state() override {
            // Return the current state, no state change in this scene
            return SCENE1; // Assuming 1 is the ID for Scene1
        }
};

#endif