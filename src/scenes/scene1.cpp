#include "include/scene1.hpp"

Scene1::Scene1(sf::RenderWindow* window, float frame_rate, std::string groundFile, std::string directory, std::string layerFiles)
:Scene(window, frame_rate, 500.0f, groundFile, directory, layerFiles) {
    player = std::make_unique<Player>(frame_rate, 100, window->getSize().y - 200, -10,0);      
    // zombies.push_back(std::make_unique<NormalZombie>(frame_rate, 500, window->getSize().y - 200, player.get()));
    // zombies.push_back(std::make_unique<RunnerZombie>(frame_rate, 500, window->getSize().y - 200, player.get()));
    zombies.push_back(std::make_unique<FlyingZombie>(frame_rate, 500, window->getSize().y - 200, player.get()));
    groundBoundingBox.setOrigin(0,groundBoundingBox.getSize().y);
    groundBoundingBox.setFillColor(sf::Color::Transparent);
    groundBoundingBox.setOutlineColor(sf::Color::Blue);
    groundBoundingBox.setOutlineThickness(3);
    groundBoundingBox.setPosition(0, window->getSize().y);

    printf("scene loaded\n");

}

void Scene1::update(){
    gravity(player.get(), true);
    for (auto& zombie : zombies) {
        if (zombie->name == "FlyingZombie") {
            continue; // Skip FlyingZombie gravity handling
        }
        gravity(zombie.get(), false);
    }
    player->idle();

    
    switch (horizDir) {
        case 'A':
            if (!player->atk_animation.status) {
                player->run_animation.state = 0;
                break;
            }

            player->posX -= player->speed * frame_rate;
            if (player->posX < 100) {
                player->posX = 100; // Prevent going out of bounds

                float moveX = player->speed * frame_rate;
                moveX = safeEdgeX(moveX, ground);
                
                for (auto& zombie : zombies) {
                    zombie->posX += moveX; 
                }

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
            if (!player->atk_animation.status) {
                player->run_animation.state = 0;
                break;
            }

            player->posX += player->speed * frame_rate;
            if (player->posX > window->getSize().x - 100) {
                player->posX = window->getSize().x - 100; // Prevent going out of bounds

                float moveX = -(player->speed * frame_rate);
                moveX = safeEdgeX(moveX, ground);
                
                for (auto& zombie : zombies) {
                    zombie->posX += moveX; 
                }

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
        case 'Z':
            if (player->boundingBox.getGlobalBounds().intersects(groundBoundingBox.getGlobalBounds())) {
                player->jump = true;
            }
            break;
    }

    if (fire){
        player->atk();
        if (player->atk_animation.status) {
            fire = false; // Reset fire state after attack animation completes
        }
    }

    player->jumping(gravityForce);
    player->update();
    
    for (int i = 0; i < zombies.size(); i++) {
        zombies[i]->update();
        if (zombies[i]->isDead) {
            zombies.erase(zombies.begin() + i);
            continue; // Skip dead zombies
        }
    }

}

void Scene1::render(sf::RenderTarget & target) {
    window->clear(sf::Color(30, 53, 59));

    for (unsigned long i = layerSprite.size(); i > 0; i--) {
        window->draw(layerSprite[i-1]);
    }
    window->draw(ground);
    window->draw(groundBoundingBox);
    window->draw(player->sprite);

    for (auto& zombie : zombies) {
        window->draw(zombie->sprite);
    }
    
    window->draw(player->boundingBox);
    
    for (auto& zombie : zombies) {
        window->draw(zombie->boundingBox);
    }
}

void Scene1::handle_event(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                horizDir = 'A';
                break;
            case sf::Keyboard::Right:
                horizDir = 'D';
                break;
            case sf::Keyboard::Z:
                vertDir = 'Z';
                break;
            default:
                break;
        }
    }else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                horizDir = '\0';
                break;
            case sf::Keyboard::Right:
                horizDir = '\0';
                break;
            case sf::Keyboard::Z:
                vertDir = '\0';
                break;
            default:
                break;
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X) {
        fire = true;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {              
        zombies.push_back(std::make_unique<NormalZombie>(frame_rate, 500, window->getSize().y - 200, player.get()));
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {              
        zombies.push_back(std::make_unique<RunnerZombie>(frame_rate, 500, window->getSize().y - 200, player.get()));
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {              
        zombies.push_back(std::make_unique<FlyingZombie>(frame_rate, 500, window->getSize().y - 200, player.get()));
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        printf("Escape key pressed, exiting scene.\n");
        window->close(); // Close the window when Escape is pressed
        exit(0);
    }

}

int Scene1::get_next_state() {
    // Return the current state, no state change in this scene
    return SCENE1; // Assuming 1 is the ID for Scene1
}