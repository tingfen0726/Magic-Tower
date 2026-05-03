#include "App.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    SDL_StopTextInput();

    // 遊戲初始化
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

    // 樓層與商店管理
    m_LevelManager = std::make_shared<LevelManager>(m_Map, m_Player, m_Renderer);
    m_LevelManager->InitFloorData();
    m_Map->SetVisible(false);

    m_ShopManager = std::make_shared<ShopManager>(m_Player.get());

    // 戰鬥管理
    m_BattleManager = std::make_shared<BattleManager>(m_Player.get(), m_Toast);

    // 介面與總管
    m_UIManager = std::make_shared<UIManager>(m_Player, m_LevelManager, m_Renderer);

    m_GameFlowManager = std::make_shared<GameFlowManager>(
        m_Player, m_LevelManager, m_BattleManager, m_ShopPanel,
        m_NPCDialog, m_FloorChangePanel, m_EnemyInfoPanel, m_Toast
    );

    // 其他邏輯管理
    m_ItemManager = std::make_shared<ItemManager>(m_Player, m_Toast);
    m_NPCManager = std::make_shared<NPCManager>(m_Player, m_LevelManager, m_NPCDialog, m_Toast);
    m_MovementManager = std::make_shared<MovementManager>(
        m_Player, m_Map, m_LevelManager, m_ItemManager,
        m_BattleManager, m_NPCManager, m_BattlePanel, m_ShopPanel, m_NPCDialog
    );

    // 戰鬥事件
    m_BattleManager->OnPlayerHpChanged = [this](int newHp) { m_BattlePanel->UpdatePlayerHpText(newHp); };
    m_BattleManager->OnEnemyHpChanged = [this](int newHp) { m_BattlePanel->UpdateEnemyHpText(newHp); };
    m_BattleManager->OnBattleEnded = [this](bool playerWon) {
        m_BattlePanel->ClosePanel();
        m_GameFlowManager->ProcessBattleResult(playerWon);
    };

    // 商店事件
    m_ShopPanel->OnConfirmPurchase = [this](int shopID, int optionIndex) {
        return m_ShopManager->ProcessPurchase(shopID, optionIndex);
    };

    m_CurrentState = State::UPDATE;
}