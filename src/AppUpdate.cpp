#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/GameObject.hpp"

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    // 遊戲初始化觸發
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_CurrentState == State::UPDATE) {
        m_Background->StartGame();
        m_Player->SetVisible(true);
        m_Map->SetVisible(true);
        m_PlayerIcon->SetVisible(true);
        m_UIManager->SetHUDVisible(true);
    }
    // 更新基礎物件狀態
    m_Player->Update();
    m_Map->Update();
    m_Toast->Update();
    m_NPCDialog->Update();
    m_FloorChangePanel->Update();
    m_EnemyInfoPanel->Update();
    if (m_BattleManager->GetIsActive()) {
        m_BattleManager->Update();
    }

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

    m_UIManager->UpdateHUD();
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
            m_FloorChangePanel->ShowFloorChangePanel(m_Player->GetInventory().haswindCompass);
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
}
