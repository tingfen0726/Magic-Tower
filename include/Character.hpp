#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_CHARACTER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_CHARACTER_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Map.hpp"
class Character : public Util::GameObject {
public:
    Character(const std::string& path, float zIndex)
    : GameObject(std::make_unique<Util::Image>(path), zIndex) {}

    virtual ~Character() = default;
    virtual void Update() = 0;

protected:
    float m_Speed = 5.0f;
};


#endif //REPLACE_WITH_YOUR_PROJECT_NAME_CHARACTER_HPP