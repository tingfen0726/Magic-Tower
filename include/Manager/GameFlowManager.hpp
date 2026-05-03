#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GAMEFLOWMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GAMEFLOWMANAGER_HPP

#include <memory>
#include <vector>
#include "Player.hpp"
#include "Manager/LevelManager.hpp"
#include "Manager/BattleManager.hpp"
#include "UIText/ShopPanel.hpp"
#include "UIText/NPCDialog.hpp"
#include "UIText/FloorChangePanel.hpp"
#include "UIText/EnemyInfoPanel.hpp"
#include "UIText/Toast.hpp"
#include "Block/Enemy.hpp"

class GameFlowManager {
public:
    GameFlowManager(std::shared_ptr<Player> player,
                    std::shared_ptr<LevelManager> levelManager,
                    std::shared_ptr<BattleManager> battleManager,
                    std::shared_ptr<ShopPanel> shopPanel,
                    std::shared_ptr<NPCDialog> npcDialog,
                    std::shared_ptr<FloorChangePanel> floorChangePanel,
                    std::shared_ptr<EnemyInfoPanel> enemyInfoPanel,
                    std::shared_ptr<Toast> toast);

    bool IsPlayerLockedByUI();
    void ProcessBattleResult(bool isWin);
    void ProcessShopLogic();
    void ProcessFloorChange();

    void SetCurrentEnemy(std::shared_ptr<Enemy> enemy) { m_CurrentEnemy = enemy; }
    std::shared_ptr<Enemy> GetCurrentEnemy() { return m_CurrentEnemy; }

private:
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<LevelManager> m_LevelManager;
    std::shared_ptr<BattleManager> m_BattleManager;
    std::shared_ptr<ShopPanel> m_ShopPanel;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<FloorChangePanel> m_FloorChangePanel;
    std::shared_ptr<EnemyInfoPanel> m_EnemyInfoPanel;
    std::shared_ptr<Toast> m_Toast;

    std::shared_ptr<Enemy> m_CurrentEnemy = nullptr;
};



#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GAMEFLOWMANAGER_HPP