#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEMANAGER_HPP

#include "Player.hpp"
#include "Block/Enemy.hpp"
#include <functional>
#include "UIText/Toast.hpp"

class BattleManager {
public:
    BattleManager(Player* player, std::shared_ptr<Toast> toast);

    std::function<void(int)> OnPlayerHpChanged;
    std::function<void(int)> OnEnemyHpChanged;
    std::function<void(bool)> OnBattleEnded;

    bool GetIsActive() const { return m_IsActive; }

    void StartBattle(EnemyStats enemyStats);

    void Update();

private:
    Player* m_Player;
    std::shared_ptr<Toast> m_Toast;
    EnemyStats m_CurrentEnemy;
    int m_ActionCooldown = 0;
    bool m_IsActive = false;
};
#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEMANAGER_HPP