#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_ENEMY_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_ENEMY_HPP
struct EnemyStats {
    int hp = 0;     // 生命
    int atk = 0;    // 攻擊
    int def = 0;    // 防禦
    int gold = 0;   // 金幣
    int exp = 0;    // 經驗值
    float loss = 0; // 損失
};
#include "Map.hpp"

class Enemy : public Block {
public:
    Enemy(const std::vector<std::string>& imagePath, int x, int y, int id);
    void UpdateAnimation() override;
    EnemyStats GetEnemyStats() {return m_Stats;}
    int GetAllHpLoss();
    bool GetIsdie() {return m_Isdie;}
    void SetIsdie(bool isdie) {m_Isdie = isdie;}
    std::vector<std::string> GetImagePath() {return {m_imagePath[0], m_imagePath[1]};}
private:
    EnemyStats m_Stats;
    bool m_Isdie = false;
    std::vector<std::string> m_imagePath;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_ENEMY_HPP