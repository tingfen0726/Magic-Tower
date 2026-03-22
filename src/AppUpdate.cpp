#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"

void App::Update() {
    if (m_Player->GetFloorChangeRequest()) {
        ChangeFloor(m_Player->GetFloorChangeRequest());
        m_Player->ClearFloorChangeRequest();
    }
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_CurrentState == State::UPDATE) {
        m_Background->StartGame();
        m_Player->SetVisible(true);
        m_Map->SetVisible(true);
    }
    m_Player->Update(m_Map);
    m_Map->Update();
    auto playerstate = m_Player->GetPlayerStats();
    m_PlayerStatUI[0]->UpdateValue("Level: ", playerstate.level);
    m_PlayerStatUI[1]->UpdateValue("HP: ", playerstate.hp);
    m_PlayerStatUI[2]->UpdateValue("ATK: ", playerstate.atk);
    m_PlayerStatUI[3]->UpdateValue("DEF: ", playerstate.def);
    m_PlayerStatUI[4]->UpdateValue("GOLD: ", playerstate.gold);
    m_PlayerStatUI[5]->UpdateValue("EXP: ", playerstate.exp);
    auto playerkey = m_Player->GetInventory();
    m_PlayerKeyUI[0]->UpdateValue("Yellow Key: ", playerkey.yellowKey);
    m_PlayerKeyUI[1]->UpdateValue("Blue Key: ", playerkey.blueKey);
    m_PlayerKeyUI[2]->UpdateValue("Red Key: ", playerkey.redKey);


    m_Renderer.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
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
