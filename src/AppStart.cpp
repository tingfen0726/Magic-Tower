#include "App.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    SDL_StopTextInput();

    // 遊戲初始化


    m_GameFlowManager = std::make_shared<GameFlowManager>();
    m_GameFlowManager->Initialize();

    m_CurrentState = State::UPDATE;
}