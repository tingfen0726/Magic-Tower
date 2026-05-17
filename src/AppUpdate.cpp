#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    switch (m_GameState) {
        case GameState::TITLE_SCREEN:                   // 遊戲初始化觸發
            if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_CurrentState == State::UPDATE) {
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
            m_GameFlowManager->Update();

            HandleSystemInput();

            //處理核心遊戲流程
            if (!m_GameFlowManager->IsPlayerLockedByUI()) {
                auto encounteredEnemy = m_MovementManager->ProcessPlayerMovement();
                if (encounteredEnemy != nullptr) {
                    m_GameFlowManager->SetCurrentEnemy(encounteredEnemy);
                }
            }
            else {
                m_Player->StopMove();
            }

            // 邏輯結算
            m_GameFlowManager->ProcessShopLogic();
            m_NPCManager->ProcessNPCLogic();
            m_GameFlowManager->ProcessFloorChange();
            m_GameFlowManager->ProcessLoadData();

            m_UIManager->UpdateHUD();
            break;
    }
    m_Renderer.Update();
}

std::vector<std::shared_ptr<Enemy>> App::GetEnemy() {
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

void App::HandleSystemInput() {
    if (Util::Input::IsKeyDown(Util::Keycode::F)) {
        if (m_FloorChangePanel->GetVisible()) {
            m_FloorChangePanel->CloseFloorChangePanel();
        }
        else if (!m_GameFlowManager->IsPlayerLockedByUI()) {
            m_FloorChangePanel->ShowFloorChangePanel(m_Player->GetInventory().haswindCompass, m_Player->GetCheatingMode());
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        if (m_EnemyInfoPanel->GetVisible()) {
            m_EnemyInfoPanel->CloseEnemyInfoPanel();
        }
        else if (!m_GameFlowManager->IsPlayerLockedByUI() && m_Player->GetInventory().hasgodknifesign) {
            m_EnemyInfoPanel->ShowEnemyInfoPanel(m_Player->GetPlayerStats(), GetEnemy());
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        if (!m_GameFlowManager->IsPlayerLockedByUI()) {
            m_GameFlowManager->ResetGame();
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::P)) {
        if (!m_GameFlowManager->IsPlayerLockedByUI()) {
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
        else if (!m_GameFlowManager->IsPlayerLockedByUI()) {
            m_Selectpanel->ShowSelectpanel(m_SaveManager->GetLatestSaveFiles());
        }
    }

}
