#include "Manager/GameFlowManager.hpp"
#include "GameConstants.hpp"
#include "Util/Logger.hpp"

#include "BackgroundImage.hpp"

// 實體物件
#include "Player.hpp"
#include "Map.hpp"
#include "Block/Enemy.hpp"

// UI 介面
#include "UIText/Toast.hpp"
#include "UIText/BattlePanel.hpp"
#include "UIText/ShopPanel.hpp"
#include "UIText/NPCDialog.hpp"
#include "UIText/FloorChangePanel.hpp"
#include "UIText/EnemyInfoPanel.hpp"
#include "UIText/GameClearPanel.hpp"
#include "UIText/Selectpanel.hpp"

#include "Manager/ShopManager.hpp"
#include "Manager/BattleManager.hpp"
#include "Manager/LevelManager.hpp"
#include "Manager/ItemManager.hpp"
#include "Manager/NPCManager.hpp"
#include "Manager/MovementManager.hpp"
#include "Manager/UIManager.hpp"
#include "Manager/SaveManager.hpp"

GameFlowManager::GameFlowManager() {

}

void GameFlowManager::Initialize() {
    m_Background = std::make_shared<BackgroundImage>();
    m_Renderer.AddChild(m_Background);

    m_Player = std::make_shared<Player>();
    m_Player->SetVisible(false);
    m_Renderer.AddChild(m_Player);

    m_Map = std::make_shared<Map>();

    // 玩家頭像
    m_PlayerIcon = std::make_shared<Util::GameObject>();
    m_PlayerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Player/player_11.bmp"));
    m_PlayerIcon->m_Transform.translation = {-345.0f, 270.0f};
    m_PlayerIcon->SetVisible(false);
    m_Renderer.AddChild(m_PlayerIcon);

    // UI 面板初始化
    m_Toast = std::make_shared<Toast>("找我嗎?");
    m_Renderer.AddChild(m_Toast);

    m_BattlePanel = std::make_shared<BattlePanel>();
    m_Renderer.AddChild(m_BattlePanel);

    m_ShopPanel = std::make_shared<ShopPanel>();
    m_Renderer.AddChild(m_ShopPanel);

    m_NPCDialog = std::make_shared<NPCDialog>();
    m_Renderer.AddChild(m_NPCDialog);

    m_FloorChangePanel = std::make_shared<FloorChangePanel>();
    m_Renderer.AddChild(m_FloorChangePanel);

    m_EnemyInfoPanel = std::make_shared<EnemyInfoPanel>();
    m_Renderer.AddChild(m_EnemyInfoPanel);

    m_GameClearPanel = std::make_shared<GameClearPanel>();
    m_Renderer.AddChild(m_GameClearPanel);

    m_Selectpanel = std::make_shared<Selectpanel>();
    m_Renderer.AddChild(m_Selectpanel);

    // 樓層與商店管理
    m_LevelManager = std::make_shared<LevelManager>(m_Map, m_Player, m_Renderer);
    m_LevelManager->InitFloorData();

    m_ShopManager = std::make_shared<ShopManager>(m_Player.get());

    // 戰鬥管理
    m_BattleManager = std::make_shared<BattleManager>(m_Player.get(), m_Toast);

    // 介面與總管
    m_UIManager = std::make_shared<UIManager>(m_Player, m_LevelManager, m_Renderer);



    // 其他邏輯管理
    m_ItemManager = std::make_shared<ItemManager>(m_Player, m_Toast);
    m_NPCManager = std::make_shared<NPCManager>(m_Player, m_LevelManager, m_NPCDialog, m_Toast);
    m_MovementManager = std::make_shared<MovementManager>(
        m_Player, m_Map, m_LevelManager, m_ItemManager,
        m_BattleManager, m_NPCManager, m_BattlePanel, m_ShopPanel, m_NPCDialog
    );
    m_SaveManager = std::make_shared<SaveManager>(m_LevelManager, m_Player);

    // 戰鬥事件
    m_BattleManager->OnPlayerHpChanged = [this](int newHp) { m_BattlePanel->UpdatePlayerHpText(newHp); };
    m_BattleManager->OnEnemyHpChanged = [this](int newHp) { m_BattlePanel->UpdateEnemyHpText(newHp); };
    m_BattleManager->OnBattleEnded = [this](bool playerWon) {
        m_BattlePanel->ClosePanel();
        ProcessBattleResult(playerWon);
    };
    m_BattleManager->OnShowVictoryHint = [this]() { m_BattlePanel->ShowVictoryHint(); };

    // 商店事件
    m_ShopPanel->OnConfirmPurchase = [this](int shopID, int optionIndex) {
        return m_ShopManager->ProcessPurchase(shopID, optionIndex);
    };

    ResetGame();
    m_Map->SetVisible(false);
}

bool GameFlowManager::IsPlayerLockedByUI() {
    return m_ShopPanel->GetVisible() ||
           m_NPCDialog->GetIsDialogue() ||
           m_BattleManager->GetIsActive() ||
           m_FloorChangePanel->GetVisible() ||
           m_EnemyInfoPanel->GetVisible() ||
           m_GameClearPanel->GetVisible() ||
           m_Selectpanel->GetVisible();
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
            }
            else if (m_CurrentEnemy->GetID() == Config::ID::OCTOPUS && m_LevelManager->GetCurrentFloor() == 24) {
                m_LevelManager->ChangeRemoteBlock(24, 4, 1, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 5, 1, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 6, 1, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 4, 2, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 5, 2, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 6, 2, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 4, 3, Config::ID::EMPTY);
                m_LevelManager->ChangeRemoteBlock(24, 6, 3, Config::ID::EMPTY);
                m_GameClearPanel->ShowGameClearPanel();

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

void GameFlowManager::ProcessLoadData() {
    std::string filename =  m_Selectpanel->ChangeOptions();
    if (filename != "") {
        LoadGame(filename);
    }
}

void GameFlowManager::RestoreGameState(const GameSaveData &data) {
    m_Player->SetStats(PlayerLabel::Stat::LEVEL, data.player_stats.level);
    m_Player->SetStats(PlayerLabel::Stat::HP, data.player_stats.hp);
    m_Player->SetStats(PlayerLabel::Stat::ATK, data.player_stats.atk);
    m_Player->SetStats(PlayerLabel::Stat::DEF, data.player_stats.def);
    m_Player->SetStats(PlayerLabel::Stat::GOLD, data.player_stats.gold);
    m_Player->SetStats(PlayerLabel::Stat::EXP, data.player_stats.exp);

    m_Player->SetKey(PlayerLabel::Key::YELLOW, data.player_inventory.yellowKey);
    m_Player->SetKey(PlayerLabel::Key::BLUE, data.player_inventory.blueKey);
    m_Player->SetKey(PlayerLabel::Key::RED, data.player_inventory.redKey);

    m_Player->SetItem(PlayerLabel::Item::HOLYCROSS, data.player_inventory.hasholyCross);
    m_Player->SetItem(PlayerLabel::Item::REDVERI, data.player_inventory.hasredveri);
    m_Player->SetItem(PlayerLabel::Item::BLUEVERI, data.player_inventory.hasblueveri);
    m_Player->SetItem(PlayerLabel::Item::GREENVERI, data.player_inventory.hasgreenveri);
    m_Player->SetItem(PlayerLabel::Item::GEMHOE, data.player_inventory.hasgemhoe);
    m_Player->SetItem(PlayerLabel::Item::GODKNIFESIGN, data.player_inventory.hasgodknifesign);
    m_Player->SetItem(PlayerLabel::Item::WINDCOMPASS, data.player_inventory.haswindCompass);

    m_Player->SetChCheatingMode(data.Cheating_Mode);

    m_LevelManager->RestoreLevelState(data.m_FloorData, data.m_CurrentFloor);
    m_Player->SetPosition(data.playerGridX, data.playerGridY);

}

void GameFlowManager::ResetGame() {
    m_LevelManager->InitFloorData();
    GameSaveData initialData;

    initialData.player_stats = {1, 1000, 10, 10, 0, 0};
    initialData.player_inventory = PlayerInventory();
    initialData.m_FloorData = m_LevelManager->GetFloorData();
    initialData.m_CurrentFloor = 0;
    initialData.playerGridX = 5;
    initialData.playerGridY = 10;
    initialData.Cheating_Mode = false;

    RestoreGameState(initialData);
}

void GameFlowManager::LoadGame(const std::string &filename) {
    GameSaveData initialData;
    if (m_SaveManager->LoadGame(filename, initialData)) {
        for (auto& floordate : initialData.m_FloorData) {
            m_LevelManager->CreateNPCs(floordate);
        }
        RestoreGameState(initialData);
    }
    else {
        m_Toast->SetColor(Util::Color{180, 0, 0, 255});
        m_Toast->ShowToast("載入失敗!??");
    }
}

std::vector<std::shared_ptr<Enemy>> GameFlowManager::GetEnemy() {
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

void GameFlowManager::HandleSystemInput() {
    if (Util::Input::IsKeyDown(Util::Keycode::F)) {
        if (m_FloorChangePanel->GetVisible()) {
            m_FloorChangePanel->CloseFloorChangePanel();
        }
        else if (!IsPlayerLockedByUI()) {
            m_FloorChangePanel->ShowFloorChangePanel(m_Player->GetInventory().haswindCompass, m_Player->GetCheatingMode());
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        if (m_EnemyInfoPanel->GetVisible()) {
            m_EnemyInfoPanel->CloseEnemyInfoPanel();
        }
        else if (!IsPlayerLockedByUI() && m_Player->GetInventory().hasgodknifesign) {
            m_EnemyInfoPanel->ShowEnemyInfoPanel(m_Player->GetPlayerStats(), GetEnemy());
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        if (!IsPlayerLockedByUI()) {
            ResetGame();
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::P)) {
        if (!IsPlayerLockedByUI()) {
            if (m_SaveManager->SaveGame()) {
                m_Toast->SetColor(Util::Color{180, 150, 0, 255});
                m_Toast->ShowToast("儲存成功!");
            }
            else {
                m_Toast->SetColor(Util::Color{180, 0, 0, 255});
                m_Toast->ShowToast("儲存失敗!??");
            }
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::O)) {
        if (m_Selectpanel->GetVisible()) {
            m_Selectpanel->CloseSelectpanel();
        }
        else if (!IsPlayerLockedByUI()) {
            m_Selectpanel->ShowSelectpanel(m_SaveManager->GetLatestSaveFiles());
        }
    }
}


void GameFlowManager::Update() {
    switch (m_GameState) {
        case GameState::TITLE_SCREEN:                   // 遊戲初始化觸發
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
                m_Background->StartGame();
                m_Player->SetVisible(true);
                m_Map->SetVisible(true);
                m_PlayerIcon->SetVisible(true);
                m_UIManager->SetHUDVisible(true);
                m_GameState = GameState::PLAYING;
            }
            break;
        case GameState::PLAYING:                        // 更新基礎物件狀態
            m_Map->Update();

            HandleSystemInput();

            //處理核心遊戲流程
            if (!IsPlayerLockedByUI()) {
                auto encounteredEnemy = m_MovementManager->ProcessPlayerMovement();
                if (encounteredEnemy != nullptr) {
                    SetCurrentEnemy(encounteredEnemy);
                }
            }
            else {
                m_Player->StopMove();
            }

            // 邏輯結算
            ProcessShopLogic();
            m_NPCManager->ProcessNPCLogic();
            ProcessFloorChange();
            ProcessLoadData();

            m_UIManager->UpdateHUD();
            break;
    }

    m_Renderer.Update();
    m_Player->Update();
    m_Toast->Update();
    m_NPCDialog->Update();
    m_FloorChangePanel->Update();
    m_EnemyInfoPanel->Update();
    m_GameClearPanel->Update();
    if (m_BattleManager->GetIsActive()) {
        m_BattleManager->Update();
    }
    m_Selectpanel->Update();
}
