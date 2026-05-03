#include "Manager/GameFlowManager.hpp"
#include "GameConstants.hpp"
#include "Util/Logger.hpp"

GameFlowManager::GameFlowManager(
    std::shared_ptr<Player> player, std::shared_ptr<LevelManager> levelManager,
    std::shared_ptr<BattleManager> battleManager, std::shared_ptr<ShopPanel> shopPanel,
    std::shared_ptr<NPCDialog> npcDialog, std::shared_ptr<FloorChangePanel> floorChangePanel,
    std::shared_ptr<EnemyInfoPanel> enemyInfoPanel, std::shared_ptr<Toast> toast)
    : m_Player(player), m_LevelManager(levelManager), m_BattleManager(battleManager),
      m_ShopPanel(shopPanel), m_NPCDialog(npcDialog), m_FloorChangePanel(floorChangePanel),
      m_EnemyInfoPanel(enemyInfoPanel), m_Toast(toast) {

}

bool GameFlowManager::IsPlayerLockedByUI() {
    return m_ShopPanel->GetVisible() ||
           m_NPCDialog->GetIsDialogue() ||
           m_BattleManager->GetIsActive() ||
           m_FloorChangePanel->GetVisible() ||
           m_EnemyInfoPanel->GetVisible();
}

void GameFlowManager::ProcessBattleResult(bool isWin) {
    if (isWin) {
        if (m_CurrentEnemy != nullptr) {
            int dropGold = m_CurrentEnemy->GetEnemyStats().gold;
            int dropExp = m_CurrentEnemy->GetEnemyStats().exp;
            m_Player->AddStats(PlayerLabel::Stat::GOLD, dropGold);
            m_Player->AddStats(PlayerLabel::Stat::EXP, dropExp);
            m_CurrentEnemy->SetIsdie(true); // 怪物死亡

            if (m_CurrentEnemy->GetID() == Config::ID::MAGIC_SERGEANT_A_1 && m_LevelManager->GetCurrentFloor() == 16) {
                m_LevelManager->EnemyReinforcements(1);
            }

            if (m_CurrentEnemy->GetID() == Config::ID::VAMPIRE_1 && m_LevelManager->GetCurrentFloor() == 19) {
                std::vector<DialogueStage> DialogueStages = {
                    {{
                        {Speaker::VAMPIRE, "　看不出來你還有兩下子，\n有本事的話來21樓。"},
                        {Speaker::VAMPIRE, "　在那裡，你就可以見識\n到我真正的實力了!"}
                    }, false}
                };
                m_NPCDialog->StartDialog(DialogueStages[0].dialogues);
            }
            else if (m_CurrentEnemy->GetID() == Config::ID::VAMPIRE_2 && m_LevelManager->GetCurrentFloor() == 21) {
                std::vector<DialogueStage> DialogueStages = {
                    {{
                        {Speaker::VAMPIRE, "　啊......\n怎麼可能，我怎麼可能"},
                        {Speaker::VAMPIRE, "會被你打被呢!\n　不，不要這樣............"}
                    }, false}
                };
                m_NPCDialog->StartDialog(DialogueStages[0].dialogues);
                m_LevelManager->EnemyReinforcements(2);
                m_LevelManager->ChangeRemoteBlock(21, 5, 1, Config::ID::STAIRS_UP);
                LOG_INFO("Where's my staircase?");
            }
        }
    }
    else {
        LOG_INFO("You're a bit dead.");
        // m_CurrentState = State::END;
    }
    m_CurrentEnemy = nullptr;
}
void GameFlowManager::ProcessFloorChange() {
    int ptr = m_FloorChangePanel->ChangeOptions();
    if (ptr >= 0) {
        if (!m_LevelManager->JumpToFloor(ptr, true)) {
            m_Toast->SetColor(Util::Color{180, 0, 0, 255});
            m_Toast->ShowToast("該樓層尚未開啟!");
        } else {
            auto targetFloorData = m_LevelManager->GetFloorData()[ptr];
            m_Player->SetPosition(targetFloorData.flyX, targetFloorData.flyY);
        }
    }
}

void GameFlowManager::ProcessShopLogic() {
    m_ShopPanel->ChangeOptions();
    if (m_ShopPanel->GetTradeFail()) {
        m_Toast->SetColor(Util::Color{180, 0, 0, 255});
        m_Toast->ShowToast("資源不足，交易失敗！");
        m_ShopPanel->ResetTradeFail();
    }
}
