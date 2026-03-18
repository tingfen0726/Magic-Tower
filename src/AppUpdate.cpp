#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_CurrentState == State::UPDATE) {
        m_Background->StartGame();
        m_Player->SetVisible(true);
        m_Map->SetVisible(true);
    }
    m_Player->Update(m_Map);
    m_Map->Update();



    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}