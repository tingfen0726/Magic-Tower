#include "Manager/NPCManager.hpp"
#include "Config.hpp"

NPCManager::NPCManager(std::shared_ptr<Player> player, std::shared_ptr<LevelManager> levelManager, std::shared_ptr<NPCDialog> npcDialog, std::shared_ptr<Toast> toast)
    : m_Player(player), m_LevelManager(levelManager), m_NPCDialog(npcDialog), m_Toast(toast) {

}

void NPCManager::ProcessNPCLogic() {
    // if (!m_CurrentNPC) return;
    m_NPCDialog->NextDialogue();

    if (!m_NPCDialog->GetIsDialogue() && m_CurrentNPC != nullptr) {
        int stage = m_CurrentNPC->GetCurrentStage();
        if (m_CurrentNPC->GetID() == Config::ID::FAIRY_0) {
            if (stage == 0) {
                int currentX = m_CurrentNPC->GetPosition()[0];
                int currentY = m_CurrentNPC->GetPosition()[1];
                // 移仙子，鋪地
                m_LevelManager->MoveNPC(m_CurrentNPC, currentX - 1, currentY);
                m_LevelManager->ChangeRemoteBlock(0, currentX, currentY, Config::ID::EMPTY);

                m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
                m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
                m_Player->AddKey(PlayerLabel::Key::RED, 1);
                m_CurrentNPC->AddCurrentStage();
            }
            else if (stage == 3) {
                m_Player->AddStats(PlayerLabel::Stat::ATK, m_Player->GetPlayerStats().atk * 1.0f / 3.0f);
                m_Player->AddStats(PlayerLabel::Stat::DEF, m_Player->GetPlayerStats().def * 1.0f / 3.0f);
                m_Player->AddStats(PlayerLabel::Stat::HP, m_Player->GetPlayerStats().hp * 1.0f / 3.0f);
                m_LevelManager->ChangeRemoteBlock(20, 5, 7, Config::ID::STAIRS_UP);
            }
            m_CurrentNPC->IsCompleted();
        }
        else if (m_CurrentNPC->GetID() == Config::ID::THIEF_4) {
            m_CurrentNPC->IsCompleted();
            if (stage == 0) {
                m_CurrentNPC->SetCurrentStage(1);
                m_LevelManager->ChangeRemoteBlock(2, 1, 6, Config::ID::EMPTY);
            }
            else if (stage == 1) {
            }
            else if (stage == 2) {
                m_Player->SetItem(PlayerLabel::Item::GEMHOE, false);
                m_LevelManager->ChangeRemoteBlock(18, 5, 8, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(18, 5, 9, Config::ID::EMPTY);
                m_CurrentNPC->IsCompleted();
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::ELDER_2) {
            if (stage == 0) {
                m_Player->AddStats(PlayerLabel::Stat::ATK, 70);
                m_Toast->ShowToast("獲得 鋼劍 攻擊力 +70");
                m_CurrentNPC->IsCompleted();
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::SHOPKEEPER_2) {
            if (stage == 0) {
                m_Player->AddStats(PlayerLabel::Stat::DEF, 70);
                m_Toast->ShowToast("獲得 鋼盾 防護力 +70");
                m_CurrentNPC->IsCompleted();
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::ELDER_15) {
            if (stage == 1) {
                m_Player->AddStats(PlayerLabel::Stat::GOLD, -500);
                m_Player->AddStats(PlayerLabel::Stat::ATK, 120);
                m_Toast->ShowToast("獲得 聖光劍 攻擊力 +120");
                m_CurrentNPC->IsCompleted();
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::SHOPKEEPER_15) {
            if (stage == 1) {
                m_Player->AddStats(PlayerLabel::Stat::EXP, -500);
                m_Player->AddStats(PlayerLabel::Stat::DEF, 120);
                m_Toast->ShowToast("獲得 星光盾 防護力 +120");
                m_CurrentNPC->IsCompleted();
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::ELDER_16) {
            m_Player->SetItem(PlayerLabel::Item::BLUEVERI, true);
            m_Toast->ShowToast("獲得 神秘寶物!");
            m_CurrentNPC->IsCompleted();
        }
        else if (m_CurrentNPC->GetID() == Config::ID::PRINCESS) {
            if (stage == 0) {
                m_CurrentNPC->IsCompleted();
                m_CurrentNPC->AddCurrentStage();
                m_LevelManager->ChangeRemoteBlock(18, 10, 10, Config::ID::STAIRS_UP); //有問題
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::VAMPIRE_19) {
            if (stage == 0) {
                m_CurrentNPC->IsCompleted();
            }
        }
        else if (m_CurrentNPC->GetID() == Config::ID::SYSTEM_NPC) {
            m_CurrentNPC->IsCompleted();
            if (stage == 1) {
                m_Player->SetStats(PlayerLabel::Stat::ATK, 5000);
                m_Player->SetStats(PlayerLabel::Stat::DEF, 5000);
                m_Player->SetStats(PlayerLabel::Stat::GOLD, 5000);
                m_Player->SetStats(PlayerLabel::Stat::EXP, 5000);

                m_Player->SetKey(PlayerLabel::Key::YELLOW, 100);
                m_Player->SetKey(PlayerLabel::Key::BLUE, 100);
                m_Player->SetKey(PlayerLabel::Key::RED, 100);

                m_Player->SetItem(PlayerLabel::Item::BLUEVERI, true);
                m_Player->SetItem(PlayerLabel::Item::GEMHOE, true);
                m_Player->SetItem(PlayerLabel::Item::GODKNIFESIGN, true);
                m_Player->SetItem(PlayerLabel::Item::GREENVERI, true);
                m_Player->SetItem(PlayerLabel::Item::REDVERI, true);
                m_Player->SetItem(PlayerLabel::Item::WINDCOMPASS, true);
                m_Player->SetItem(PlayerLabel::Item::HOLYCROSS, true);
                for (int i = 0; i < m_LevelManager->GetFloorData().size(); i++) {
                    m_LevelManager->GetFloorData()[i].isVisited = true;
                }
            }
            m_CurrentNPC->AddCurrentStage();
        }

        // if (!isSpecialNPC) {
        //     m_CurrentNPC->IsCompleted();
        //     m_CurrentNPC->AddCurrentStage();
        // }
        m_CurrentNPC = nullptr;
    }
}