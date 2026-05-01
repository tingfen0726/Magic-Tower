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
    void UpdatePlayerHpText(int hp);
    void UpdateEnemyHpText(int hp);
    void ClosePanel();
private:
    std::vector<std::shared_ptr<UIText>> m_text;
    std::vector<std::shared_ptr<UIText>> m_text2;
    std::shared_ptr<Util::GameObject> m_PlayerIcon;
    std::shared_ptr<Util::GameObject> m_EnemyIcon;

    const float xOffset = 200.0f;
    const float yOffset = 175.0f;
    const float startY = 200.0f;

    const float iconY = 138.0f;
    const float iconX = 345.0f;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEPANEL_HPP