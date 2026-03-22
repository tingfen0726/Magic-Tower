#include "App.hpp"
#include "Util/Logger.hpp"
float stateFontX = -280.0f; // 往右移一點，避開中文字
float stateFontY = 210.0f;  // 往下移一點，對齊「等級」的那一行
float spacing = 42.0f;      // 稍微拉大間距，讓它跟著中文字的行距走

float keyFontX = -280.0f;
float keyFontY = -116.0f;
float spacing_key = 56.7f;

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
        auto textUI = std::make_shared<PlayerStatUI>(
            RESOURCE_DIR "/Font/Cubic_11_1.010_R.ttf",
            36,
            "0",
            Util::Color{255,255,255,255},
            stateFontX,
            stateFontY - (i * spacing)
        );
        textUI->SetVisible(false);
        m_PlayerStatUI.push_back(textUI);
        m_Renderer.AddChild(textUI);
    }
    for (int i = 0; i < 3; i++) {
        auto textUI = std::make_shared<PlayerKeyUI>(
            RESOURCE_DIR "/Font/Cubic_11_1.010_R.ttf",
            36,
            "0",
            Util::Color{255,255,255,255},
            keyFontX,
            keyFontY - (i * spacing_key)
        );
        textUI->SetVisible(false);
        m_PlayerKeyUI.push_back(textUI);
        m_Renderer.AddChild(textUI);
    }



    m_CurrentState = State::UPDATE;
}


