#ifndef MAGIC_TOWER_BACKGROUNDIMAGE_HPP
#define MAGIC_TOWER_BACKGROUNDIMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <iostream>
#include <string>

class BackgroundImage : public Util::GameObject {
public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR "/Image/Scene/end.BMP"), -10) {
        std::cout << "Loading Background from: " << RESOURCE_DIR "/Image/Scene/end.BMP" << std::endl;
    }

    void StartGame() {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        if (temp) {
            std::string path = std::string(RESOURCE_DIR) + "/Image/Scene/scene1.BMP";
            std::cout << "Trying to load: " << path << std::endl;
            temp->SetImage(path);
        } else {
            std::cout << "Error: Pointer cast failed!" << std::endl;
        }
    }
};

#endif // MAGIC_TOWER_BACKGROUNDIMAGE_HPP