#include "Block/Props.hpp"
//
// Created by fenfenfen on 2026/3/20.
//

Props::Props(const std::vector<std::string> &imagePath, int x, int y, int id) : Block(imagePath, x, y, id){
}

void Props::UpdateAnimation() {
    unsigned int currentTime = SDL_GetTicks();

    if (m_IsPickUp) {
        m_CurrentFrame = m_imagePath.size() - 1;
        SetImageFrame(m_CurrentFrame);
        return;
    }
    if (currentTime - m_LastFrameTime > 150) {
        m_CurrentFrame = (m_CurrentFrame + 1) % (m_imagePath.size() - 1);
        SetImageFrame(m_CurrentFrame);
        m_LastFrameTime = currentTime;
    }
}
