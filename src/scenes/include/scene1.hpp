#ifndef SCENE1_HPP
#define SCENE1_HPP

#include "scenes/include/scene.hpp"
#include "characters/include/player.hpp"
#include "characters/include/zombie.hpp"
#include "characters/include/flyingZombie.hpp"
#include "characters/include/normalZombie.hpp"
#include "characters/include/runnerZombie.hpp"

class Scene1: public Scene, public State {
    private:
        std::unique_ptr<Player> player = nullptr;
        std::vector<std::unique_ptr<Zombie>> zombies; // Vector to hold multiple zombies
        std::vector<std::unique_ptr<Zombie>> flyingZombies;

        // Directional keys
        char horizDir = '\0'; // 'A' for left, 'D' for right
        char vertDir = '\0'; // 'W' for up, 'S' for down
        sf::Vector2<float> mousePos;
        bool fire = false;

        // Gravity force
        const float gravityForce = 980.0f; // Adjust as needed for your game physics

    public:

        Scene1(sf::RenderWindow* window, float frame_rate = (1.0f / 60.0f), std::string groundFile="", std::string directory="", std::string layerFiles="");
        void update() override;
        void render(sf::RenderTarget & target) override;
        void handle_event(sf::Event event) override;
        int get_next_state() override;
};

#endif