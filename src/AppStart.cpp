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
    for (int i = 0; i < 6; i++) {
        std::string mapPath = std::string(RESOURCE_DIR) + "/Map/level" + std::to_string(i) + ".txt";
        m_FloorData.push_back(LoadFloorFromFile(mapPath));
    }
    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer.AddChild(block);
    }
    m_Map->SetVisible(false);
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
    m_floorUI = std::make_shared<UIText>( 36, "0 樓", Util::Color{255,255,255,255}, 155, 335);
    m_floorUI->SetVisible(false);
    m_Renderer.AddChild(m_floorUI);

    for (int i = 0; i < 6; i++) {   //測試資料，需刪
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
    m_ShopPanel = std::make_shared<ShopPanel>();
    m_Renderer.AddChild(m_ShopPanel);

    m_CurrentState = State::UPDATE;
}


