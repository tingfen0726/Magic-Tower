#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEPANEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEPANEL_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"
#include "Block/Enemy.hpp"
#include "Player.hpp"

class BattlePanel : public Util::GameObject {
public:
    BattlePanel();
    void ShowBattlePanel(PlayerStats playerStats, EnemyStats enemyStats, std::string imagePath);
    bool GetIsFinished() const { return m_IsFinished; }
    bool GetIsActive() const { return m_IsActive; }
    void ResetFinished() { m_IsFinished = false; }
    void Update();
private:
    std::vector<std::shared_ptr<UIText>> m_text;
    std::vector<std::shared_ptr<UIText>> m_text2;
    std::shared_ptr<Util::GameObject> m_PlayerIcon;
    std::shared_ptr<Util::GameObject> m_EnemyIcon;

    int m_timer = 0;
    PlayerStats m_Pstate;
    EnemyStats m_Estate;

    int m_ActionCooldown = 0;
    bool m_IsActive = false;    //戰鬥中
    bool m_IsFinished = false;  //動畫
    const float xOffset = 200.0f;
    const float yOffset = 175.0f;
    const float startY = 200.0f;

    const float iconY = 138.0f;
    const float iconX = 345.0f;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEPANEL_HPP