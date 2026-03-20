#include "App.hpp"
#include "Util/Logger.hpp"

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

    m_CurrentState = State::UPDATE;
}

/*







 */


