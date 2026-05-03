#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_MOVEMENTMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_MOVEMENTMANAGER_HPP

#include <memory>
#include "Player.hpp"
#include "Map.hpp"
#include "Manager/LevelManager.hpp"
#include "Manager/ItemManager.hpp"
#include "Manager/BattleManager.hpp"
#include "Manager/NPCManager.hpp"
#include "UIText//BattlePanel.hpp"
#include "UIText/ShopPanel.hpp"
#include "UIText/NPCDialog.hpp"

#include "Block/Door.hpp"
#include "Block/Props.hpp"
#include "Block/Enemy.hpp"
#include "Block/Stair.hpp"
#include "Block/Shop.hpp"
#include "Block/NPC.hpp"
#include "GameConstants.hpp"

class MovementManager {
public:
    MovementManager(std::shared_ptr<Player> player, std::shared_ptr<Map> map,
                    std::shared_ptr<LevelManager> levelManager, std::shared_ptr<ItemManager> itemManager,
                    std::shared_ptr<BattleManager> battleManager, std::shared_ptr<NPCManager> npcManager,
                    std::shared_ptr<BattlePanel> battlePanel, std::shared_ptr<ShopPanel> shopPanel,
                    std::shared_ptr<NPCDialog> npcDialog);

    // 🌟 注意：改為回傳 Enemy 指標！
    std::shared_ptr<Enemy> ProcessPlayerMovement();

private:
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Map> m_Map;
    std::shared_ptr<LevelManager> m_LevelManager;
    std::shared_ptr<ItemManager> m_ItemManager;
    std::shared_ptr<BattleManager> m_BattleManager;
    std::shared_ptr<NPCManager> m_NPCManager;
    std::shared_ptr<BattlePanel> m_BattlePanel;
    std::shared_ptr<ShopPanel> m_ShopPanel;
    std::shared_ptr<NPCDialog> m_NPCDialog;
};




#endif //REPLACE_WITH_YOUR_PROJECT_NAME_MOVEMENTMANAGER_HPP