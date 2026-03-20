#include "Block/Props.hpp"
//
// Created by fenfenfen on 2026/3/20.
//

Props::Props(const std::vector<std::string> &imagePath, int x, int y, int id) : Block(imagePath, x, y, id){
}

void Props::UpdateAnimation() {
    if (m_IsPickUp == false) {
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
