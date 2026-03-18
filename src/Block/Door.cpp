#include "Block/Door.hpp"
#include "config.hpp"
#include "Constants.hpp"


Door::Door(const std::vector<std::string> &imagePath, int x, int y, int id): Block(imagePath, x, y, id) {
}

void Door::Open() {
    if (m_IsOpen == false && m_CurrentFrame == 0) {
        m_IsOpen = true;
    }
}

void Door::UpdateAnimation() {
    if (m_IsOpen == false) {
        return;
    }

    unsigned int currentTime = SDL_GetTicks();

    if (currentTime - m_LastFrameTime > 300)  {
        m_CurrentFrame++;
        if (m_CurrentFrame >= m_imagePath.size()) {
            return;
        }
        SetImageFrame(m_CurrentFrame);
        m_LastFrameTime = currentTime;
    }
}

bool Door::CanOpen(std::vector<int> keys) {
    if (m_IsOpen) { return true; }
    switch (m_ID) {
        case Config::ID::DOOR_YELLOW:
            if (keys[0] >= 1) { Open(); return true; }
            return false;
            break;
        case Config::ID::DOOR_BLUE:
            if (keys[1] >= 1) { Open(); return true; }
            return false;
            break;
        case Config::ID::DOOR_RED:
            if (keys[2] >= 1) { Open(); return true; }
            return false;
            break;
        case Config::ID::DOOR_GREEN:
            return false;
        case Config::ID::DOOR_IRON:
            Open();
            return true;
    }
}