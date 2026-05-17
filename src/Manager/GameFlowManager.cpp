#include "Manager/GameFlowManager.hpp"
#include "GameConstants.hpp"
#include "Util/Logger.hpp"

GameFlowManager::GameFlowManager(
    std::shared_ptr<Player> player, std::shared_ptr<LevelManager> levelManager,
    std::shared_ptr<BattleManager> battleManager, std::shared_ptr<SaveManager> saveManager
    , std::shared_ptr<ShopPanel> shopPanel,
    std::shared_ptr<NPCDialog> npcDialog, std::shared_ptr<FloorChangePanel> floorChangePanel,std::shared_ptr<EnemyInfoPanel> enemyInfoPanel,
    std::shared_ptr<Selectpanel> selectpanel
    ,std::shared_ptr<Toast> toast, std::shared_ptr<GameClearPanel> gameClearPanel)
    : m_Player(player), m_LevelManager(levelManager), m_BattleManager(battleManager),
      m_SaveManager(saveManager),
      m_ShopPanel(shopPanel), m_NPCDialog(npcDialog), m_FloorChangePanel(floorChangePanel),
      m_Selectpanel(selectpanel),
      m_EnemyInfoPanel(enemyInfoPanel), m_Toast(toast), m_GameClearPanel(gameClearPanel) {

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

void GameFlowManager::Update() {
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
