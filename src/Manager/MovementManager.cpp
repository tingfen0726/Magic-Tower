#include "Manager/MovementManager.hpp"

MovementManager::MovementManager(
    std::shared_ptr<Player> player, std::shared_ptr<Map> map,
    std::shared_ptr<LevelManager> levelManager, std::shared_ptr<ItemManager> itemManager,
    std::shared_ptr<BattleManager> battleManager, std::shared_ptr<NPCManager> npcManager,
    std::shared_ptr<BattlePanel> battlePanel, std::shared_ptr<ShopPanel> shopPanel,
    std::shared_ptr<NPCDialog> npcDialog)
    : m_Player(player), m_Map(map), m_LevelManager(levelManager), m_ItemManager(itemManager),
      m_BattleManager(battleManager), m_NPCManager(npcManager),
      m_BattlePanel(battlePanel), m_ShopPanel(shopPanel), m_NPCDialog(npcDialog) {

}

std::shared_ptr<Enemy> MovementManager::ProcessPlayerMovement() {
    int nextX, nextY, nextDir;
    m_Player->GetNextGrid(nextX, nextY, nextDir);

    if (nextX != m_Player->GetCurrentGridX() || nextY != m_Player->GetCurrentGridY()) {

        auto levelData = m_Map->GetLevelData();
        auto blocks = m_Map->GetBlocks();
        if (nextY >= 0 && nextY < 11 && nextX >= 0 && nextX < 11) {
            int targetID = levelData[nextY][nextX];
            if (targetID >= Config::ID::WALL_BEGIN && targetID <= Config::ID::WALL_END) {
                m_Player->StepInPlace(nextDir);
                return nullptr;
            }
            if (targetID >= Config::ID::DOOR_BEGIN && targetID <= Config::ID::DOOR_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto doorPtr = std::dynamic_pointer_cast<Door>(block);
                        if (doorPtr) {
                            if (doorPtr->IsFullyOpen()) { }
                            else if (!doorPtr->IsOpen()) {
                                if (doorPtr->CanOpen({m_Player->GetInventory().yellowKey, m_Player->GetInventory().blueKey, m_Player->GetInventory().redKey})) {
                                    switch (doorPtr->GetID()) {
                                        case Config::ID::DOOR_YELLOW: m_Player->AddKey(PlayerLabel::Key::YELLOW, -1); break;
                                        case Config::ID::DOOR_BLUE: m_Player->AddKey(PlayerLabel::Key::BLUE, -1);   break;
                                        case Config::ID::DOOR_RED: m_Player->AddKey(PlayerLabel::Key::RED, -1); break;
                                    }
                                    m_Player->StepInPlace(nextDir);
                                    return nullptr;
                                }

                                else{
                                    m_Player->StepInPlace(nextDir);
                                    return nullptr;
                                }
                            }
                            else {
                                m_Player->StepInPlace(nextDir);
                                return nullptr;
                            }
                        }
                    }
                }
            }
            if (targetID >= Config::ID::STAIRS_BEGIN && targetID <= Config::ID::STAIRS_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto stairPtr = std::dynamic_pointer_cast<Stair>(block);
                        if (stairPtr) {
                            // m_Player->MoveToGrid(nextX, nextY, nextDir);
                            m_LevelManager->ProcessStair(nextX, nextY);
                            return nullptr;
                        }
                    }
                }
            }

            if (targetID >= Config::ID::ITEM_BEGIN && targetID <= Config::ID::ITEM_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto propsPtr = std::dynamic_pointer_cast<Props>(block);
                        if (propsPtr) {
                            m_ItemManager->ProcessItemPickup(propsPtr);
                        }
                    }
                }
            }
            if (targetID >= Config::ID::ENEMY_BEGIN && targetID <= Config::ID::ENEMY_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto enemyPtr = std::dynamic_pointer_cast<Enemy>(block);
                        if (enemyPtr) {
                            m_BattleManager->StartBattle(enemyPtr->GetEnemyStats());
                            m_BattlePanel->ShowBattlePanel(m_Player->GetPlayerStats(), enemyPtr->GetEnemyStats(), enemyPtr->GetImagePath()[0]);
                            m_Player->StepInPlace(nextDir);
                            return enemyPtr;
                        }
                    }
                }
            }
            if (targetID >= Config::ID::SHOP_BEGIN && targetID <= Config::ID::SHOP_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto shopPtr = std::dynamic_pointer_cast<Shop>(block);
                        if (shopPtr) {
                            m_ShopPanel->ShowShopPanel(targetID);
                            m_Player->StepInPlace(nextDir);
                            return nullptr;
                        }
                    }
                }
            }
            if (targetID >= Config::ID::NPC_BEGIN && targetID <= Config::ID::NPC_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto NPCPtr = std::dynamic_pointer_cast<NPC>(block);
                        if (NPCPtr) {
                            if (NPCPtr->GetID() == Config::ID::FAIRY_0) {
                                if ((NPCPtr->GetCurrentStage() == 2) && m_Player->GetInventory().hasholyCross) {
                                    NPCPtr->SetCurrentStage(3);
                                }
                                if ((NPCPtr->GetCurrentStage() == 1) && m_Player->GetInventory().hasblueveri) {
                                    NPCPtr->SetCurrentStage(2);
                                }
                            }
                            if (NPCPtr->GetID() == Config::ID::THIEF_4) {
                                if ((NPCPtr->GetCurrentStage() == 1) && m_Player->GetInventory().hasgemhoe) {
                                    NPCPtr->SetCurrentStage(2);
                                    }
                            }
                            if (NPCPtr->GetID() == Config::ID::SHOPKEEPER_15 && m_Player->GetPlayerStats().exp >= 500) {
                                NPCPtr->SetCurrentStage(1);
                            }
                            if (NPCPtr->GetID() == Config::ID::ELDER_15 && m_Player->GetPlayerStats().gold >= 500) {
                                NPCPtr->SetCurrentStage(1);
                            }

                            std::vector<DialogueStage> dialogueStage = NPCPtr->GetDialogues();
                            if (m_NPCManager->GetCurrentNPC() == nullptr) {
                                m_NPCDialog->StartDialog(dialogueStage[NPCPtr->GetCurrentStage()].dialogues);
                                m_NPCManager->InteractWith(NPCPtr);
                            }
                            m_Player->StepInPlace(nextDir);
                            return nullptr;
                        }
                    }
                }
            }
            m_Player->MoveToGrid(nextX, nextY, nextDir);
        }
    }
    return nullptr;
}