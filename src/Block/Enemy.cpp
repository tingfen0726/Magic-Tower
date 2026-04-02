#include "Block/Enemy.hpp"
#include "EnemyDatabase.hpp"

Enemy::Enemy(const std::vector<std::string> &imagePath, int x, int y, int id) : Block(imagePath, x, y, id) {
    auto it = EnemyDatabase::Data.find(id);
    if (it != EnemyDatabase::Data.end()) { m_Stats = it->second;}
    else { m_Stats = {10, 0, 0, 0, 0, 0}; }
    m_imagePath = imagePath;
}

void Enemy::UpdateAnimation() {
    unsigned int currentTime = SDL_GetTicks();

    if (m_Isdie) {
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

int Enemy::GetAllHpLoss() {
    return m_Stats.loss;
}


