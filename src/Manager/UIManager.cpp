#include "Manager/UIManager.hpp"
#include "util/Logger.hpp"

UIManager::UIManager(std::shared_ptr<Player> player, std::shared_ptr<LevelManager> levelManager, Util::Renderer& renderer)
    : m_Player(player), m_LevelManager(levelManager) {

    float stateFontX = -280.0f;
    float stateFontY = 210.0f;
    float spacing = 42.0f;

    float keyFontX = -280.0f;
    float keyFontY = -116.0f;

    // 1. 建立玩家數值 UI
    for (int i = 0; i < 6; i++) {
        auto textUI = std::make_shared<UIText>(
            36, "0", Util::Color{255,255,255,255},
            stateFontX, stateFontY - (i * spacing)
        );
        textUI->SetVisible(false);
        m_PlayerUI.push_back(textUI);
        renderer.AddChild(textUI); // 加進畫布
    }

    for (int i = 0; i < 3; i++) {
        auto textUI = std::make_shared<UIText>(
            36, "0", Util::Color{255,255,255,255},
            keyFontX, keyFontY - (i * Config::TILE_SIZE)
        );
        textUI->SetVisible(false);
        m_PlayerUI.push_back(textUI);
        renderer.AddChild(textUI);
    }

    m_floorUI = std::make_shared<UIText>(36, "序 章", Util::Color{255,255,255,255}, 155, 335);
    m_floorUI->SetVisible(false);
    renderer.AddChild(m_floorUI);

    for (int i = 0; i < 7; i++) {       //測試資料，需刪
        auto textUI = std::make_shared<UIText>(
            20, "0", Util::Color{0,0,0,255},
            (i - 2) * Config::TILE_SIZE * 2, -335.0f
        );
        m_TryTextUI.push_back(textUI);
        renderer.AddChild(textUI);
    }
}

void UIManager::UpdateHUD() {
    if (!m_Player || !m_LevelManager) return;

    int currentFloor = m_LevelManager->GetCurrentFloor();
    if (currentFloor == 0) {
        m_floorUI->UpdateText("序 章");
    }
    else if (currentFloor == 25 || currentFloor == 26){
        m_floorUI->UpdateText("第 23 層");
    }
    else {
        m_floorUI->UpdateText("第 " + std::to_string(currentFloor) + " 層");
    }

    m_PlayerUI[PlayerUI::LEVEL]->UpdateValue(m_Player->GetPlayerStats().level);
    m_PlayerUI[PlayerUI::HP]->UpdateValue(m_Player->GetPlayerStats().hp);
    m_PlayerUI[PlayerUI::ATK]->UpdateValue(m_Player->GetPlayerStats().atk);
    m_PlayerUI[PlayerUI::DEF]->UpdateValue(m_Player->GetPlayerStats().def);
    m_PlayerUI[PlayerUI::GOLD]->UpdateValue(m_Player->GetPlayerStats().gold);
    m_PlayerUI[PlayerUI::EXP]->UpdateValue(m_Player->GetPlayerStats().exp);

    m_PlayerUI[PlayerUI::YELLOW]->UpdateValue(m_Player->GetInventory().yellowKey);
    m_PlayerUI[PlayerUI::BLUE]->UpdateValue(m_Player->GetInventory().blueKey);
    m_PlayerUI[PlayerUI::RED]->UpdateValue(m_Player->GetInventory().redKey);

    m_TryTextUI[0]->UpdateText(std::string("HC: ") + (m_Player->GetInventory().hasholyCross ? "true" : "false"));
    m_TryTextUI[1]->UpdateText(std::string("RV: ") + (m_Player->GetInventory().hasredveri ? "true" : "false"));
    m_TryTextUI[2]->UpdateText(std::string("BV: ") + (m_Player->GetInventory().hasblueveri ? "true" : "false"));
    m_TryTextUI[3]->UpdateText(std::string("GV: ") + (m_Player->GetInventory().hasgreenveri ? "true" : "false"));
    m_TryTextUI[4]->UpdateText(std::string("GH: ") + (m_Player->GetInventory().hasgemhoe ? "true" : "false"));
    m_TryTextUI[5]->UpdateText(std::string("GKS: ") + (m_Player->GetInventory().hasgodknifesign ? "true" : "false"));
    m_TryTextUI[6]->UpdateText(std::string("WC: ") + (m_Player->GetInventory().haswindCompass ? "true" : "false"));
}

void UIManager::SetHUDVisible(bool visible) {
    for (auto ui : m_PlayerUI) ui->SetVisible(visible);
    if (m_floorUI) m_floorUI->SetVisible(visible);
}