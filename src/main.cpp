#include <fstream>
#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>

#include "include/character.hpp"
#include "include/scene.hpp"


int main() {
    
    float frame_rate = 1.0f/60.0f;
    printf("Frame rate: %f\n", frame_rate);

    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    window.setFramerateLimit(60);

    // Load player and scene
    Player player1(frame_rate, 88, 486);
    Scene1 scene1(&window, &player1, frame_rate, "./scene/scene1/ground.png", "./scene/scene1/", "layer");
    
    // Main loop
    while (window.isOpen()) {
        window.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
                window.close();
            }
        }
        
        scene1.keyEvent = '\0';
        scene1.horizDir = '\0';
        scene1.vertDir = '\0';

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            window.close();
            return 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            scene1.horizDir = 'A';   
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            scene1.horizDir = 'D';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            scene1.vertDir = 'W';
        }
        
        scene1.update();
        window.display();
        
    }

    return 0;
}