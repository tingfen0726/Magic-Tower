#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_CurrentState == State::UPDATE) {
        m_Background->StartGame();
        m_Player->SetVisible(true);
        m_Map->SetVisible(true);
        m_floorUI->SetVisible(true);
        m_PlayerIcon->SetVisible(true);
        for (auto ui : m_PlayerUI) { ui->SetVisible(true);}
    }
    m_Player->Update();
    m_Map->Update();
    m_Toast->Update();
    // m_BattlePanel->Update();
    // m_ShopPanel->Update();
    if (m_BattleManager->GetIsActive()) {
        m_BattleManager->Update();
    }
    m_NPCDialog->Update();
    m_FloorChangePanel->Update();
    m_EnemyInfoPanel->Update();
    if (!IsPlayerLockedByUI()) {
        ProcessPlayerMovement();
    }
    else {
        m_Player->StopMove();
    }
    ProcessShopLogic();
    ProcessNPCLogic();
    ProcessFloorChange();
    // auto& playerstate = m_Player->GetPlayerStats();
    // auto& playerkey = m_Player->GetInventory();
    if (Util::Input::IsKeyDown(Util::Keycode::F)) {
        if (!m_FloorChangePanel->GetVisible()) {
            m_FloorChangePanel->ShowFloorChangePanel(m_Player->GetInventory().haswindCompass);
        }
        else {
            m_FloorChangePanel->CloseFloorChangePanel();
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        if (!m_EnemyInfoPanel->GetVisible() && m_Player->GetInventory().hasgodknifesign) {
            m_EnemyInfoPanel->ShowEnemyInfoPanel(m_Player->GetPlayerStats(), GetEnmey());
        }
        else {
            m_EnemyInfoPanel->CloseEnemyInfoPanel();
        }
    }

    m_PlayerUI[PlayerUI::LEVEL]->UpdateValue(m_Player->GetPlayerStats().level);
    m_PlayerUI[PlayerUI::HP]->UpdateValue(m_Player->GetPlayerStats().hp);
    m_PlayerUI[PlayerUI::ATK]->UpdateValue(m_Player->GetPlayerStats().atk);
    m_PlayerUI[PlayerUI::DEF]->UpdateValue(m_Player->GetPlayerStats().def);
    m_PlayerUI[PlayerUI::GOLD]->UpdateValue(m_Player->GetPlayerStats().gold);
    m_PlayerUI[PlayerUI::EXP]->UpdateValue(m_Player->GetPlayerStats().exp);

    m_PlayerUI[PlayerUI::YELLOW]->UpdateValue(m_Player->GetInventory().yellowKey);
    m_PlayerUI[PlayerUI::BLUE]->UpdateValue(m_Player->GetInventory().blueKey);
    m_PlayerUI[PlayerUI::RED]->UpdateValue(m_Player->GetInventory().redKey);

    //測試資料，需刪
    m_TryTextUI[0]->UpdateText(std::string("HC: ") + (m_Player->GetInventory().hasholyCross ? "true" : "false"));
    m_TryTextUI[1]->UpdateText(std::string("RV: ") +(m_Player->GetInventory().hasredveri ? "true" : "false"));
    m_TryTextUI[2]->UpdateText(std::string("BV: ") +(m_Player->GetInventory().hasblueveri ? "true" : "false"));
    m_TryTextUI[3]->UpdateText(std::string("GV: ") +(m_Player->GetInventory().hasgreenveri ? "true" : "false"));
    m_TryTextUI[4]->UpdateText(std::string("GH: ") +(m_Player->GetInventory().hasgemhoe ? "true" : "false"));
    m_TryTextUI[5]->UpdateText(std::string("GKS: ") +(m_Player->GetInventory().hasgodknifesign ? "true" : "false"));
    m_TryTextUI[6]->UpdateText(std::string("WC: ") +(m_Player->GetInventory().haswindCompass ? "true" : "false"));

    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

std::vector<std::shared_ptr<Enemy>> App::GetEnmey() {
    auto blocks = m_Map->GetBlocks();
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<int> seenIDs;
    for (auto block : blocks) {
        auto enemyPtr = std::dynamic_pointer_cast<Enemy>(block);
        if (enemyPtr) {
            if (enemyPtr->GetIsdie()) continue;
            int currentID = enemyPtr->GetID();
            if (std::find(seenIDs.begin(), seenIDs.end(), currentID) == seenIDs.end()) {
                seenIDs.push_back(currentID);
                enemies.push_back(enemyPtr);
            }
        }
    }
    return enemies;
}

bool App::IsPlayerLockedByUI() {
    return m_ShopPanel->GetVisible() ||
            m_NPCDialog->GetIsDialogue() ||
            m_BattleManager->GetIsActive() ||
            m_FloorChangePanel->GetVisible() ||
            m_EnemyInfoPanel->GetVisible();
}

void App::ProcessPlayerMovement() {
    int nextX, nextY, nextDir;
    m_Player->GetNextGrid(nextX, nextY, nextDir);
    // auto& player_stats = m_Player->GetPlayerStats();
    // auto& player_inventory = m_Player->GetInventory();

    if (nextX != m_Player->GetCurrentGridX() || nextY != m_Player->GetCurrentGridY()) {

        auto levelData = m_Map->GetLevelData();
        auto blocks = m_Map->GetBlocks();
        if (nextY >= 0 && nextY < 11 && nextX >= 0 && nextX < 11) {
            int targetID = levelData[nextY][nextX];
            if (targetID >= Config::ID::WALL_BEGIN && targetID <= Config::ID::WALL_END) {
                m_Player->StepInPlace(nextDir);
                return;
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
                                    return;
                                }

                                else{
                                    m_Player->StepInPlace(nextDir);
                                    return;
                                }
                            }
                            else {
                                m_Player->StepInPlace(nextDir);
                                return;
                            }
                        }
                    }
                }
            }
            if (targetID >= Config::ID::STAIRS_BEGIN && targetID <= Config::ID::STAIRS_END) {
                if (targetID == Config::ID::STAIRS_UP) {
                    ChangeFloor(1);
                    return;
                }
                if (targetID == Config::ID::STAIRS_DOWN) {
                    ChangeFloor(-1);
                    return;
                }
            }

            if (targetID >= Config::ID::ITEM_BEGIN && targetID <= Config::ID::ITEM_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto propsPtr = std::dynamic_pointer_cast<Props>(block);
                        if (propsPtr) {
                            ProcessItemPickup(propsPtr);
                        }
                    }
                }
            }
            if (targetID >= Config::ID::ENEMY_BEGIN && targetID <= Config::ID::ENEMY_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto enemyPtr = std::dynamic_pointer_cast<Enemy>(block);
                        if (enemyPtr) {
                            if (m_CurrentEnemy == nullptr) {
                                m_CurrentEnemy = enemyPtr;
                                m_BattleManager->StartBattle(enemyPtr->GetEnemyStats());
                                m_BattlePanel->ShowBattlePanel(m_Player->GetPlayerStats(), enemyPtr->GetEnemyStats(), enemyPtr->GetImagePath()[0]);
                            }
                            m_Player->StepInPlace(nextDir);
                            return;
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
                            return;
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
                            if (m_CurrentNPC == nullptr) {
                                m_NPCDialog->StareDialog(dialogueStage[NPCPtr->GetCurrentStage()].dialogues);
                                m_CurrentNPC = NPCPtr;
                            }
                            m_Player->StepInPlace(nextDir);
                            return;
                        }
                    }
                }
            }
            m_Player->MoveToGrid(nextX, nextY, nextDir);
        }
    }
}

void App::ProcessBattleResult(bool isWin) {
    if (isWin) {
        if (m_CurrentEnemy != nullptr) {
            int dropGold = m_CurrentEnemy->GetEnemyStats().gold;
            int dropExp = m_CurrentEnemy->GetEnemyStats().exp;
            m_Player->AddStats(PlayerLabel::Stat::GOLD, dropGold);
            m_Player->AddStats(PlayerLabel::Stat::EXP, dropExp);
            m_CurrentEnemy->SetIsdie(true); // 怪物死亡

            if (m_CurrentEnemy->GetID() == Config::ID::VAMPIRE_1 && m_CurrentFloor == 19) {
                std::vector<DialogueStage> DialogueStages = {
                    {{
                        {Speaker::VAMPIRE, "　看不出來你還有兩下子，\n有本事的話來21樓。"},
                        {Speaker::VAMPIRE, "　在那裡，你就可以見識\n到我真正的實力了!"}
                    }, false}
                };
                m_NPCDialog->StareDialog(DialogueStages[0].dialogues);
            }
            else if (m_CurrentEnemy->GetID() == Config::ID::VAMPIRE_2 && m_CurrentFloor == 21) {
                std::vector<DialogueStage> DialogueStages = {
                    {{
                        {Speaker::VAMPIRE, "　啊......\n怎麼可能，我怎麼可能"},
                        {Speaker::VAMPIRE, "會被你打被呢!\n　不，不要這樣............"}
                    }, false}
                };
                m_NPCDialog->StareDialog(DialogueStages[0].dialogues);
                ChangeRemoteBlock(21, 5, 1, Config::ID::STAIRS_UP);
                LOG_INFO("Where's my staircase?");
            }
        }
    }
    else {
        LOG_INFO("You're a bit dead.");
        m_CurrentState = State::END;
    }
    m_CurrentEnemy = nullptr;
}

void App::ProcessFloorChange() {
    int ptr = m_FloorChangePanel->ChangeOptions();
    if (ptr >= 0) {
        if (!JumpToFloor(ptr)) {
            m_Toast->SetColor(Util::Color{180, 0, 0, 255});
            m_Toast->ShowToast("該樓層尚未開啟!");
        }
    }
}

void App::ProcessNPCLogic() {
    // auto& player_stats = m_Player->GetPlayerStats();
    // auto& player_inventory = m_Player->GetInventory();

    m_NPCDialog->NextDialogue();

    if (!m_NPCDialog->GetIsDialogue() && m_CurrentNPC != nullptr) {
        int stage = m_CurrentNPC->GetCurrentStage();
        if (m_CurrentNPC->GetID() == Config::ID::FAIRY_0) {
            if (stage == 0) {
                int currentX = m_CurrentNPC->GetPosition()[0];
                int currentY = m_CurrentNPC->GetPosition()[1];
                // 移仙子，鋪地
                m_Map->MoveNPC(m_CurrentNPC, currentX - 1, currentY);
                ChangeRemoteBlock(0, currentX, currentY, Config::ID::EMPTY);

                m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
                m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
                m_Player->AddKey(PlayerLabel::Key::RED, 1);
                m_CurrentNPC->AddCurrentStage();
            }
            else if (stage == 3) {
                m_Player->AddStats(PlayerLabel::Stat::ATK, m_Player->GetPlayerStats().atk * 1.0f / 3.0f);
                m_Player->AddStats(PlayerLabel::Stat::DEF, m_Player->GetPlayerStats().def * 1.0f / 3.0f);
                m_Player->AddStats(PlayerLabel::Stat::HP, m_Player->GetPlayerStats().hp * 1.0f / 3.0f);
                ChangeRemoteBlock(20, 5, 7, Config::ID::STAIRS_UP);
            }
            m_CurrentNPC->IsCompleted();
        }
        else if (m_CurrentNPC->GetID() == Config::ID::THIEF_4) {
            m_CurrentNPC->IsCompleted();
            if (stage == 0) {
                m_CurrentNPC->SetCurrentStage(1);
                ChangeRemoteBlock(2, 1, 6, Config::ID::EMPTY);
            }
            else if (stage == 1) {
            }
            else if (stage == 2) {
                m_Player->SetItem(PlayerLabel::Item::GEMHOE, false);
                ChangeRemoteBlock(18, 5, 8, Config::ID::EMPTY);
                ChangeRemoteBlock(18, 5, 9, Config::ID::EMPTY);
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
                ChangeRemoteBlock(18, 10, 10, Config::ID::STAIRS_UP); //有問題
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
                for (int i = 0; i < m_FloorData.size(); i++) {
                    m_FloorData[i].isVisited = true;
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
void App::ProcessItemPickup(std::shared_ptr<Props> propsPtr) {
    // auto& player_stats = m_Player->GetPlayerStats();
    // auto& player_inventory = m_Player->GetInventory();
    if (propsPtr->GetPickUp()) {
        return;
    }
    propsPtr->PickUp();
    switch (propsPtr->GetID()) {
        case Config::ID::YELLOW_KEY:
            m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
            m_Toast->ShowToast("獲得 黃鑰匙 x1");
            break;
        case Config::ID::BLUE_KEY:
            m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
            m_Toast->ShowToast("獲得 藍鑰匙 x1");
            break;
        case Config::ID::RED_KEY:
            m_Player->AddKey(PlayerLabel::Key::RED, 1);
            m_Toast->ShowToast("獲得 紅鑰匙 x1");
            break;
        case Config::ID::MAGIC_KEY:
            m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
            m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
            m_Player->AddKey(PlayerLabel::Key::RED, 1);
            m_Toast->ShowToast("獲得 鑰匙盒 各種鑰匙數 x1");
            break;
        case Config::ID::RED_POTION:
            m_Player->AddStats(PlayerLabel::Stat::HP, 200);
            m_Toast->ShowToast("獲得 小血瓶 體力 +200");
            break;
        case Config::ID::BLUE_POTION:
            m_Player->AddStats(PlayerLabel::Stat::HP, 500);
            m_Toast->ShowToast("獲得 大血瓶 體力 +500");
            break;
        case Config::ID::HOLY_WATER:
            m_Player->SetStats(PlayerLabel::Stat::HP, m_Player->GetPlayerStats().hp * 2);
            m_Toast->ShowToast("獲得 聖水 當前體力翻倍");
            break;
        case Config::ID::RUBY:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 3);
            m_Toast->ShowToast("獲得 紅色寶石 攻擊力 +3");
            break;
        case Config::ID::SAPPHIRE:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 3);
            m_Toast->ShowToast("獲得 藍色寶石 防禦力 +3");
            break;
        case Config::ID::SWORD_B:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 150);
            m_Toast->ShowToast("獲得 星光神劍 攻擊力 +150");
            break;
        case Config::ID::SWORD_C:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 70);
            m_Toast->ShowToast("獲得 青峰劍 攻擊力 +70");
            break;
        case Config::ID::SWORD_D:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 10);
            m_Toast->ShowToast("獲得 鐵劍 攻擊力 +10");
            break;
        case Config::ID::SHIELD_A:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 190);
            m_Toast->ShowToast("獲得 光芒神盾 防禦力 +190");
            break;
        case Config::ID::SHIELD_C:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 10);
            m_Toast->ShowToast("獲得 鐵盾 防禦力 +10");
            break;
        case Config::ID::SHIELD_D:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 85);
            m_Toast->ShowToast("獲得 黃金盾 防禦力 +85");
            break;
        case Config::ID::COIN:
            m_Player->AddStats(PlayerLabel::Stat::GOLD, 300);
            m_Toast->ShowToast("獲得 金塊 金幣 +300");
            break;
        case Config::ID::JUMP_WING_SMALL:
            m_Player->AddStats(PlayerLabel::Stat::LEVEL, 1);
            m_Toast->ShowToast("獲得 小飛羽 等級 +1");
            break;
        case Config::ID::JUMP_WING_BIG:
            m_Player->AddStats(PlayerLabel::Stat::LEVEL, 3);
            m_Toast->ShowToast("獲得 大飛羽 等級 +3");
            break;
        case Config::ID::HOLY_CROSS:
            m_Player->SetItem(PlayerLabel::Item::HOLYCROSS, true);
            m_Toast->ShowToast("獲得 神聖十字架 提升體功防屬性");
            break;
        case Config::ID::RED_VERI:
            m_Player->SetItem(PlayerLabel::Item::REDVERI, true);
            m_Toast->ShowToast("獲得 炎之靈杖");
            break;
        case Config::ID::GREEN_VERI:
            m_Player->SetItem(PlayerLabel::Item::GREENVERI, true);
            m_Toast->ShowToast("獲得 心之靈杖");
            break;
        case Config::ID::GEM_HOE:
            m_Player->SetItem(PlayerLabel::Item::GEMHOE, true);
            m_Toast->ShowToast("獲得 紅寶石榔頭");
            break;
        case Config::ID::GOD_KNIFE_SIGN:
            m_Player->SetItem(PlayerLabel::Item::GODKNIFESIGN, true);
            m_Toast->ShowToast("獲得 聖光徽");
            break;
        case Config::ID::WIND_COMPASS:
            m_Player->SetItem(PlayerLabel::Item::WINDCOMPASS, true);
            m_Toast->ShowToast("獲得 風之羅盤");
            break;
        default:
            break;
    }
}

void App::ProcessShopLogic() {
    m_ShopPanel->ChangeOptions();
    if (m_ShopPanel->GetTradeFail()) {
        m_Toast->SetColor(Util::Color{180, 0, 0, 255});
        m_Toast->ShowToast("資源不足，交易失敗！");
        m_ShopPanel->ResetTradeFail();
    }
}

void App::ChangeFloor(int floorDelta) {
    //  1上樓 -1下樓

    m_FloorData[m_CurrentFloor].grid = m_Map->GetLevelData();
    m_FloorData[m_CurrentFloor].isVisited = true;
    m_FloorData[m_CurrentFloor].savedNPCs.clear();
    for (auto block : m_Map->GetBlocks()) {
        if (auto npc = std::dynamic_pointer_cast<NPC>(block)) {
            m_FloorData[m_CurrentFloor].savedNPCs.push_back(npc);
        }
    }
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.RemoveChild(block);
    }
    m_CurrentFloor += floorDelta;


    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
    if (!m_FloorData[m_CurrentFloor].savedNPCs.empty()) {
        m_Map->RestoreNPCs(m_FloorData[m_CurrentFloor].savedNPCs);
    }
    if (m_FloorData[m_CurrentFloor].floorLevel == 0) {
        m_floorUI->UpdateText("序 章");
    }
    else {
        m_floorUI->UpdateValueText(" 樓", m_FloorData[m_CurrentFloor].floorLevel);
    }
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.AddChild(block);
    }
    if (floorDelta > 0) {
        m_Player->SetPosition(m_FloorData[m_CurrentFloor].upStairsX, m_FloorData[m_CurrentFloor].upStairsY);
    }
    else {
        m_Player->SetPosition(m_FloorData[m_CurrentFloor].downStairsX, m_FloorData[m_CurrentFloor].downStairsY);
    }
}

bool App::JumpToFloor(int targetFloor) {
    if (!m_FloorData[targetFloor].isVisited) return false;
    m_FloorData[m_CurrentFloor].grid = m_Map->GetLevelData();
    m_FloorData[m_CurrentFloor].isVisited = true;
    m_FloorData[m_CurrentFloor].savedNPCs.clear();
    for (auto block : m_Map->GetBlocks()) {
        if (auto npc = std::dynamic_pointer_cast<NPC>(block)) {
            m_FloorData[m_CurrentFloor].savedNPCs.push_back(npc);
        }
    }
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.RemoveChild(block);
    }
    m_CurrentFloor = targetFloor;

    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
    if (!m_FloorData[m_CurrentFloor].savedNPCs.empty()) {
        m_Map->RestoreNPCs(m_FloorData[m_CurrentFloor].savedNPCs);
    }
    m_floorUI->UpdateValueText(" 樓", m_FloorData[m_CurrentFloor].floorLevel);
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.AddChild(block);
    }
    m_Player->SetPosition(m_FloorData[m_CurrentFloor].upStairsX, m_FloorData[m_CurrentFloor].upStairsY);
    return true;
}

void App::ChangeRemoteBlock(int targetFloor, int x, int y, int newID) {
    if (targetFloor == m_CurrentFloor) {
        m_Map->UpdateGridID(x, y, newID);
        std::vector<std::string> floorImg = {};
        switch (newID) {
            case Config::ID::EMPTY:
                floorImg = {RESOURCE_DIR "/Image/Road/road.bmp"};
                break;
            case Config::ID::STAIRS_UP:
                floorImg = {RESOURCE_DIR "/Image/Stair/upstair.bmp"};
                LOG_INFO("image??");
        }
        auto newFloor = std::make_shared<Block>(floorImg, x, y, newID);
        newFloor->SetZIndex(25);
        m_Map->AddBlock(newFloor);
        m_Renderer.AddChild(newFloor);
    }
    else {
        m_FloorData[targetFloor].grid[y][x] = newID;
    }
}

void App::EnemyReinforcements(int stage) {
    int maxlevel = (stage == 1)? 16 : 21;
    for (int i = 0; i < maxlevel; i++) {
        auto map = m_FloorData[i].grid;
        for (int j = 0; j < map.size(); j++) {
            for (int k = 0; k < map[j].size(); k++) {
                if (stage == 1) {
                    if (map[j][k] == Config::ID::SOUL_SKELETON_1) {
                        ChangeRemoteBlock(i, k, j, Config::ID::SOUL_SKELETON_2);
                    }
                    if (map[j][k] == Config::ID::DARK_KNIGHT_1) {
                        ChangeRemoteBlock(i, k, j, Config::ID::DARK_KNIGHT_2);
                    }
                }
            }
        }
    }
}