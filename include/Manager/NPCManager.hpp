#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_NPCMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_NPCMANAGER_HPP

#include <memory>
#include "Player.hpp"
#include "LevelManager.hpp"
#include "Block/NPC.hpp"
#include "UIText/NPCDialog.hpp"
#include "UIText/Toast.hpp"

class NPCManager {
public:
    NPCManager(std::shared_ptr<Player> player,
               std::shared_ptr<LevelManager> levelManager,
               std::shared_ptr<NPCDialog> npcDialog,
               std::shared_ptr<Toast> toast);
    void InteractWith(std::shared_ptr<NPC> npc) { m_CurrentNPC = npc;}
    void ProcessNPCLogic();

    std::shared_ptr<NPC> GetCurrentNPC() const { return m_CurrentNPC; }
    void ClearCurrentNPC() { m_CurrentNPC = nullptr; }


private:
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<LevelManager> m_LevelManager;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<NPC> m_CurrentNPC;
    std::shared_ptr<Toast> m_Toast;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_NPCMANAGER_HPP