#include "include/scene.hpp"

void Scene::gravity(Character* character, bool jump) {
    sf::FloatRect characterBound = character->boundingBox.getGlobalBounds();
    sf::FloatRect groundBounds = groundBoundingBox.getGlobalBounds();
    bool isGrounded = characterBound.intersects(groundBounds);
    
    if ((!isGrounded)) {
        character->posY += gravityForce * frame_rate;
    }
    if (character->posY + characterBound.height/2.1 > groundBounds.top) {
        character->posY = groundBounds.top - characterBound.height/2.1; // Prevent going below ground
    }
}

float Scene::safeEdgeX(float moveX, sf::Sprite sprite) {
    if (moveX > 0 && sprite.getPosition().x + moveX > 0)
        return 0 - sprite.getPosition().x;

    if (moveX < 0 && sprite.getPosition().x + sprite.getGlobalBounds().width + moveX < window->getSize().x)
        return window->getSize().x - (sprite.getPosition().x + sprite.getGlobalBounds().width);
    
    return moveX;
}

Scene::Scene(sf::RenderWindow* window, float frame_rate, float gravity_force, std::string groundFile, std::string directory, std::string layerFiles){
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