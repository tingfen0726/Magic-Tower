#include "Block/NPC.hpp"

NPC::NPC(const std::vector<std::string> &imagePath, int x, int y, int id) : Block(imagePath, x, y, id){
    SetZIndex(25);
}

void NPC::UpdateAnimation() {
    unsigned int currentTime = SDL_GetTicks();

    if (currentTime - m_LastFrameTime > 150) {
        m_CurrentFrame = (m_CurrentFrame + 1) % (m_imagePath.size());
        SetImageFrame(m_CurrentFrame);
        m_LastFrameTime = currentTime;
    }
}

void NPC::AddCurrentStage() {
    if (m_currentStage >= m_DialogueStages.size() - 1) {
        return;
    }
    m_currentStage += 1;
}
