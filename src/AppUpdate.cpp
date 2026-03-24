#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_CurrentState == State::UPDATE) {
        m_Background->StartGame();
        m_Player->SetVisible(true);
        m_Map->SetVisible(true);
        for (auto ui : m_PlayerUI) { ui->SetVisible(true);}
    }
    if (m_CurrentState == State::UPDATE) {
        ProcessPlayerMovement();
    }
    m_Player->Update();
    m_Map->Update();
    m_Toast->Update();
    auto playerstate = m_Player->GetPlayerStats();
    m_PlayerUI[PlayerUI::LEVEL]->UpdateValue(playerstate.level);
    m_PlayerUI[PlayerUI::HP]->UpdateValue(playerstate.hp);
    m_PlayerUI[PlayerUI::ATK]->UpdateValue(playerstate.atk);
    m_PlayerUI[PlayerUI::DEF]->UpdateValue(playerstate.def);
    m_PlayerUI[PlayerUI::GOLD]->UpdateValue(playerstate.gold);
    m_PlayerUI[PlayerUI::EXP]->UpdateValue(playerstate.exp);
    auto playerkey = m_Player->GetInventory();
    m_PlayerUI[PlayerUI::YELLOW]->UpdateValue(playerkey.yellowKey);
    m_PlayerUI[PlayerUI::BLUE]->UpdateValue(playerkey.blueKey);
    m_PlayerUI[PlayerUI::RED]->UpdateValue(playerkey.redKey);

    //測試資料，需刪
    m_TryTextUI[0]->UpdateText(std::string("HC: ") + (playerkey.hasholyCross ? "true" : "false"));
    m_TryTextUI[1]->UpdateText(std::string("RV: ") +(playerkey.hasredveri ? "true" : "false"));
    m_TryTextUI[2]->UpdateText(std::string("BV: ") +(playerkey.hasblueveri ? "true" : "false"));
    m_TryTextUI[3]->UpdateText(std::string("GV: ") +(playerkey.hasgreenveri ? "true" : "false"));
    m_TryTextUI[4]->UpdateText(std::string("GKS: ") +(playerkey.hasgodknifesign ? "true" : "false"));
    m_TryTextUI[5]->UpdateText(std::string("WC: ") +(playerkey.haswindCompass ? "true" : "false"));

    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::ProcessPlayerMovement() {
    int nextX, nextY, nextDir;
    m_Player->GetNextGrid(nextX, nextY, nextDir);
    auto& player_stats = m_Player->GetPlayerStats();
    auto& player_inventory = m_Player->GetInventory();

    if (nextX != m_Player->GetCurrentGridX() || nextY != m_Player->GetCurrentGridY()) {

        auto levelData = m_Map->GetLevelData();
        auto blocks = m_Map->GetBlocks();
        if (nextY >= 0 && nextY < 11 && nextX >= 0 && nextX < 11) {
            int targetID = levelData[nextY][nextX];
            if (targetID >= Config::ID::WALL_BEGIN && targetID <= Config::ID::WALL_END) {
                return;
            }
            if (targetID >= Config::ID::DOOR_BEGIN && targetID <= Config::ID::DOOR_END) {
                for (auto block : blocks) {
                    if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                        auto doorPtr = std::dynamic_pointer_cast<Door>(block);
                        if (doorPtr) {
                            if (doorPtr->IsFullyOpen()) { }
                            else if (!doorPtr->IsOpen()) {
                                if (doorPtr->CanOpen({player_inventory.yellowKey, player_inventory.blueKey, player_inventory.redKey})) {
                                    switch (doorPtr->GetID()) {
                                        case Config::ID::DOOR_YELLOW: player_inventory.yellowKey--; break;
                                        case Config::ID::DOOR_BLUE:   player_inventory.blueKey--; break;
                                        case Config::ID::DOOR_RED:    player_inventory.redKey--; break;
                                    }
                                    return;
                                }
                                else{
                                    return;
                                }
                            }
                            else {
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
                        if (propsPtr && !propsPtr->GetPickUp()) {
                            propsPtr->PickUp();
                            switch (propsPtr->GetID()) {
                                case Config::ID::YELLOW_KEY:
                                    player_inventory.yellowKey++;
                                    m_Toast->ShowToast("獲得 黃鑰匙 x1");
                                    break;
                                case Config::ID::BLUE_KEY:
                                    player_inventory.blueKey++;
                                    m_Toast->ShowToast("獲得 藍鑰匙 x1");
                                    break;
                                case Config::ID::RED_KEY:
                                    player_inventory.redKey++;
                                    m_Toast->ShowToast("獲得 紅鑰匙 x1");
                                    break;
                                case Config::ID::MAGIC_KEY:
                                    player_inventory.yellowKey++;
                                    player_inventory.blueKey++;
                                    player_inventory.redKey++;
                                    m_Toast->ShowToast("獲得 鑰匙盒 各種鑰匙數 x1");
                                    break;
                                case Config::ID::RED_POTION:
                                    player_stats.hp += 200;
                                    m_Toast->ShowToast("獲得 小血瓶 體力 +200");
                                    break;
                                case Config::ID::BLUE_POTION:
                                    player_stats.hp += 500;
                                    m_Toast->ShowToast("獲得 大血瓶 體力 +500");
                                    break;
                                case Config::ID::HOLY_WATER:
                                    player_stats.hp *= 2;
                                    m_Toast->ShowToast("獲得 聖水 當前體力翻倍");
                                    break;
                                case Config::ID::RUBY:
                                    player_stats.atk += 3;
                                    m_Toast->ShowToast("獲得 紅色寶石 攻擊力 +3");
                                    break;
                                case Config::ID::SAPPHIRE:
                                    player_stats.def += 3;
                                    m_Toast->ShowToast("獲得 藍色寶石 防禦力 +3");
                                    break;
                                case Config::ID::SWORD_B:
                                    player_stats.atk += 150;
                                    m_Toast->ShowToast("獲得 星光神劍 攻擊力 +150");
                                    break;
                                case Config::ID::SWORD_C:
                                    player_stats.atk += 70;
                                    m_Toast->ShowToast("獲得 青峰劍 攻擊力 +70");
                                    break;
                                case Config::ID::SWORD_D:
                                    player_stats.atk += 10;
                                    m_Toast->ShowToast("獲得 鐵劍 攻擊力 +10");
                                    break;
                                case Config::ID::SHIELD_A:
                                    player_stats.def += 190;
                                    m_Toast->ShowToast("獲得 光芒神盾 防禦力 +190");
                                    break;
                                case Config::ID::SHIELD_C:
                                    player_stats.def += 10;
                                    m_Toast->ShowToast("獲得 鐵盾 防禦力 +10");
                                    break;
                                case Config::ID::SHIELD_D:
                                    player_stats.def += 85;
                                    m_Toast->ShowToast("獲得 黃金盾 防禦力 +85");
                                    break;
                                case Config::ID::COIN:
                                    player_stats.gold += 300;
                                    m_Toast->ShowToast("獲得 金塊 金幣 +300");
                                    break;
                                case Config::ID::JUMP_WING_SMALL:
                                    player_stats.level += 1;
                                    m_Toast->ShowToast("獲得 小飛羽 等級 +1");
                                    break;
                                case Config::ID::JUMP_WING_BIG:
                                    player_stats.level += 3;
                                    m_Toast->ShowToast("獲得 大飛羽 等級 +3");
                                    break;
                                case Config::ID::HOLY_CROSS:
                                    player_inventory.hasholyCross = true;
                                    m_Toast->ShowToast("獲得 神聖十字架 提升體功防屬性");
                                    break;
                                case Config::ID::RED_VERI:
                                    player_inventory.hasredveri = true;
                                    m_Toast->ShowToast("獲得 炎之靈杖");
                                    break;
                                case Config::ID::GREEN_VERI:
                                    player_inventory.hasgreenveri = true;
                                    m_Toast->ShowToast("獲得 心之靈杖");
                                    break;
                                case Config::ID::GOD_KNIFE_SIGN:
                                    player_inventory.hasgodknifesign = true;
                                    m_Toast->ShowToast("獲得 聖光徽");
                                    break;
                                case Config::ID::WIND_COMPASS:
                                    player_inventory.haswindCompass = true;
                                    m_Toast->ShowToast("獲得 風之羅盤");
                                    break;
                                default: break;

                            }
                        }
                    }
                }
            }
            m_Player->MoveToGrid(nextX, nextY, nextDir);
        }
    }
}

void App::ChangeFloor(int floorDelta) {
    //  1上樓 -1下樓
    m_FloorData[m_CurrentFloor].grid = m_Map->GetLevelData();
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.RemoveChild(block);
    }
    m_CurrentFloor += floorDelta;
    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
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
