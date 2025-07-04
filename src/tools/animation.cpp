#include "include/animation.hpp"

Animation::Animation(std::string texture_dir, std::string type, bool individual, int numberOfFrame, sf::Sprite* sprite, float frame_rate, float resize, int offsideX, int offsideY) {
    this->texture_directory = texture_dir;
    this->individual = individual;
    this->type = type;
    this->frame_rate = frame_rate;
    this->sprite = sprite;
    this->animation_frame = numberOfFrame;
    this->dimension[0] = dimension[0];
    this->dimension[1] = dimension[1];
    if (texture_dir == ""){
        return;
    }

    if (individual && type != "") {
        textures.resize(animation_frame);
        for (int i = 0; i < animation_frame; i++) {
            if (!textures[i].loadFromFile(texture_directory + "/" + type + "/" + std::to_string(i) + ".png")) {
                throw std::runtime_error("Failed to load texture: " + texture_directory + "/" + type + "/" + std::to_string(i) + ".png");
            }
        }

        sprite->setOrigin((textures[0].getSize().x / 2.f)+offsideX, (textures[0].getSize().y / 2.f+offsideY));
        rescaleX = (64.f / (float)textures[0].getSize().x) * resize;
        rescaleY = (64.f / (float)textures[0].getSize().y) * resize;
    }
    else{
        if (type == "") {
            return;
        }
        textures.resize(1);
        if (!textures[0].loadFromFile(texture_directory + "/" + type + ".png")) {
            throw std::runtime_error("Failed to load texture: " + texture_directory + "/" + type + ".png");
        }
        printf("Texture loaded: %s\n", (texture_directory + "/" + type + ".png").c_str());
        sprite->setTexture(textures[0]);
        sprite->setTextureRect(sf::IntRect(
            0,
            0,
            (textures[0].getSize().x / animation_frame),
            textures[0].getSize().y
        ));
        sprite->setOrigin(((textures[0].getSize().x/animation_frame) / 2.f)+offsideX, (textures[0].getSize().y / 2.f)+offsideY);
        rescaleX = (64.f / ((float)textures[0].getSize().x/animation_frame)) * resize;
        rescaleY = (64.f / (float)textures[0].getSize().y) * resize;
    }
}

void Animation::animate(float animationPerSeccond){
    if (individual){
        sprite->setTexture(textures[(int)state % animation_frame]);
        if (state >= animation_frame) {
            state = 0;
        }
        state += (frame_rate * animation_frame * animationPerSeccond);
    }
    else{
        sprite->setTexture(textures[0]);
        sprite->setTextureRect(sf::IntRect(
            ((int)state % animation_frame) * (textures[0].getSize().x / animation_frame),
            0,
            (textures[0].getSize().x / animation_frame),
            textures[0].getSize().y
        ));
        if ((int)state >= animation_frame) {
            state = 0;
        }
        state += (frame_rate * animation_frame * animationPerSeccond);
    }

    if ((int)state == animation_frame){
        status = true;
    }else{
        status = false;
    }
}