//
// Created by fenfenfen on 2026/3/17.
//
#include "Block/Wall.hpp"
#include "config.hpp"

Wall::Wall(const std::vector<std::string> &imagePath, int x, int y, int id): Block(imagePath, x, y, id) {
}

void Wall::UpdateAnimation() {
    unsigned int currentTime = SDL_GetTicks();

    if (currentTime - m_LastFrameTime > 300) {
        m_CurrentFrame = (m_CurrentFrame + 1) % m_imagePath.size();
        SetImageFrame(m_CurrentFrame);
        m_LastFrameTime = currentTime;
    }
}

