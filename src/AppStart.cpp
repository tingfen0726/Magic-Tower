#include "App.hpp"

float stateFontX = -280.0f;
float stateFontY = 210.0f;
float spacing = 42.0f;

float keyFontX = -280.0f;
float keyFontY = -116.0f;

void App::Start() {
    LOG_TRACE("Start");
    SDL_StopTextInput();

    m_Background = std::make_shared<BackgroundImage>();
    m_Renderer.AddChild(m_Background);
    m_Player = std::make_shared<Player>();
    m_Renderer.AddChild(m_Player);
    m_Player->SetVisible(false);

    m_Map = std::make_shared<Map>();
    for (int i = 0; i < 22; i++) {
        std::string mapPath = std::string(RESOURCE_DIR) + "/Map/level" + std::to_string(i) + ".txt";
        m_FloorData.push_back(LoadFloorFromFile(mapPath));
    }
    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.AddChild(block);
    }
    m_Map->SetVisible(false);
    m_PlayerIcon = std::make_shared<Util::GameObject>();
    m_PlayerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Player/player_11.bmp"));
    // m_PlayerIcon->m_Transform.scale = {0.75, 0.75};
    m_PlayerIcon->m_Transform.translation = {-345.0f, 270.0f};
    m_PlayerIcon->SetVisible(false);
    m_Renderer.AddChild(m_PlayerIcon);
    for (int i = 0; i < 6; i++) {
        auto textUI = std::make_shared<UIText>(
            36,
            "0",
            Util::Color{255,255,255,255},
            stateFontX,
            stateFontY - (i * spacing)
        );
        textUI->SetVisible(false);
        m_PlayerUI.push_back(textUI);
        m_Renderer.AddChild(textUI);
    }
    for (int i = 0; i < 3; i++) {
        auto textUI = std::make_shared<UIText>(
            36,
            "0",
            Util::Color{255,255,255,255},
            keyFontX,
            keyFontY - (i * Config::TILE_SIZE)
        );
        textUI->SetVisible(false);
        m_PlayerUI.push_back(textUI);
        m_Renderer.AddChild(textUI);
    }
    m_floorUI = std::make_shared<UIText>( 36, "序 章", Util::Color{255,255,255,255}, 155, 335);
    m_floorUI->SetVisible(false);
    m_Renderer.AddChild(m_floorUI);

    for (int i = 0; i < 7; i++) {   //測試資料，需刪
        auto textUI = std::make_shared<UIText>(
            20,
            "0",
            Util::Color{0,0,0,255},
            (i - 2) * Config::TILE_SIZE * 2,
            -335.0f
        );
        m_TryTextUI.push_back(textUI);
        m_Renderer.AddChild(textUI);
    }
    m_Toast = std::make_shared<Toast>("找我嗎?");
    m_Renderer.AddChild(m_Toast);

    m_BattlePanel = std::make_shared<BattlePanel>();
    m_Renderer.AddChild(m_BattlePanel);
    m_BattleManager = std::make_shared<BattleManager>(m_Player.get());
    m_BattleManager->OnPlayerHpChanged = [this](int newHp) {
        m_BattlePanel->UpdatePlayerHpText(newHp);
    };

    m_BattleManager->OnEnemyHpChanged = [this](int newHp) {
        m_BattlePanel->UpdateEnemyHpText(newHp);
    };

    m_BattleManager->OnBattleEnded = [this](bool playerWon) {
        m_BattlePanel->ClosePanel();
        ProcessBattleResult(playerWon);
    };

    m_ShopPanel = std::make_shared<ShopPanel>();
    m_Renderer.AddChild(m_ShopPanel);
    m_ShopManager = std::make_shared<ShopManager>(m_Player.get());
    m_ShopPanel->OnConfirmPurchase = [this](int shopID, int optionIndex) {
        return m_ShopManager->ProcessPurchase(shopID, optionIndex);
    };// 依賴注入

    m_NPCDialog = std::make_shared<NPCDialog>();
    m_Renderer.AddChild(m_NPCDialog);

    m_FloorChangePanel = std::make_shared<FloorChangePanel>();
    m_Renderer.AddChild(m_FloorChangePanel);

    m_EnemyInfoPanel = std::make_shared<EnemyInfoPanel>();
    m_Renderer.AddChild(m_EnemyInfoPanel);

    m_CurrentState = State::UPDATE;
}


