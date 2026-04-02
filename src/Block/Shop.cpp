#include "Block/Shop.hpp"

Shop::Shop(const std::vector<std::string>& imagePath, int x, int y, int id) : Block(imagePath, x, y, id) {

}

void Shop::UpdateAnimation() {
    unsigned int currentTime = SDL_GetTicks();

    if (currentTime - m_LastFrameTime > 150) {
        m_CurrentFrame = (m_CurrentFrame + 1) % m_imagePath.size();
        SetImageFrame(m_CurrentFrame);
        m_LastFrameTime = currentTime;
    }
}
