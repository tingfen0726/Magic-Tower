#include "UIText/BattlePanel.hpp"

BattlePanel::BattlePanel() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Enemy/Fighting.bmp"));
    m_Transform.translation = {0, 100.0f};
    SetZIndex(98);

    m_PlayerIcon = std::make_shared<Util::GameObject>();
    m_PlayerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Enemy/player.BMP"));
    m_PlayerIcon->m_Transform.translation = {iconX, iconY};
    m_PlayerIcon->m_Transform.scale = {0.95, 0.95};
    m_PlayerIcon->SetZIndex(99);
    m_PlayerIcon->SetVisible(false);
    AddChild(m_PlayerIcon);

    m_EnemyIcon = std::make_shared<Util::GameObject>();
    m_EnemyIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Enemy/player.BMP"));
    m_EnemyIcon->m_Transform.translation = {-iconX, iconY};
    m_EnemyIcon->m_Transform.scale = {0.95, 0.95};
    m_EnemyIcon->SetZIndex(99);
    m_EnemyIcon->SetVisible(false);
    AddChild(m_EnemyIcon);
    std::vector<std::string> title = {"體力值:\n", "攻擊力:\n", "防禦力:\n"};
    SetVisible(false);
    for (int i = 0; i < 6; i++) {
        auto text = std::make_shared<UIText>(30, title[i%3], Util::Color{255,255,255,255}, 0, 0);
        float x = (i < 3) ? -xOffset : xOffset;
        float y = startY - (i % 3) * 100.0f;
        text->SetPosition(x, y);
        text->SetZIndex(99);
        m_text.push_back(text);
        text->SetVisible(false);
        AddChild(text);
    }
    auto enemy_text = std::make_shared<UIText>(46, "怪 物", Util::Color{255,255,255,255}, -347.0f, 50.0f);
    enemy_text->SetZIndex(99);
    m_text2.push_back(enemy_text);
    enemy_text->SetVisible(false);
    AddChild(enemy_text);

    auto player_text = std::make_shared<UIText>(46, "勇 士", Util::Color{255,255,255,255}, 347.0f, 50.0f);
    player_text->SetZIndex(99);
    m_text2.push_back(player_text);
    player_text->SetVisible(false);
    AddChild(player_text);

    auto VS_text = std::make_shared<UIText>(72, "VS", Util::Color{255,255,255,255}, 0, 100.0f);
    VS_text->SetZIndex(99);
    m_text2.push_back(VS_text);
    VS_text->SetVisible(false);
    AddChild(VS_text);

}

void BattlePanel::ShowBattlePanel(PlayerStats playerStats, EnemyStats enemyStats, std::string imagePath) {

    if (enemyStats.loss > 0 && enemyStats.loss < 1) { playerStats.hp -= enemyStats.loss * playerStats.hp;}
    else if (enemyStats.loss >= 1) {playerStats.hp -= enemyStats.loss;}

    m_EnemyIcon->SetDrawable(std::make_shared<Util::Image>(imagePath));
    m_text[0]->UpdateText("體力值:\n" + std::to_string(enemyStats.hp));
    m_text[1]->UpdateText("攻擊力:\n" + std::to_string(enemyStats.atk));
    m_text[2]->UpdateText("防禦力:\n" + std::to_string(enemyStats.def));
    m_text[3]->UpdateText("體力值:\n" + std::to_string(playerStats.hp));
    m_text[4]->UpdateText("攻擊力:\n" + std::to_string(playerStats.atk));
    m_text[5]->UpdateText("防禦力:\n" + std::to_string(playerStats.def));

    m_Pstate = playerStats;
    m_Estate = enemyStats;

    m_ActionCooldown = 20;
    m_timer = 9999;
    m_IsActive = true;
    SetVisible(true);
    for (int i = 0;i < 6; i++) { m_text[i]->SetVisible(true);}
    for (int i = 0;i < 3; i++) { m_text2[i]->SetVisible(true);}
    m_PlayerIcon->SetVisible(true);
    m_EnemyIcon->SetVisible(true);
}

void BattlePanel::Update() {
    if (!m_IsActive){ return;}
    if (m_Pstate.hp > 0 && m_Estate.hp > 0) {
        m_ActionCooldown--;
        if (m_ActionCooldown <= 0) {
            float critRate = std::min(1.0f, m_Pstate.level * 0.005f);
            int Dnorm = std::max(0,m_Pstate.atk - m_Estate.def);
            m_Estate.hp -= static_cast<int>(Dnorm * (1.0f + critRate));
            if (m_Estate.hp < 0) m_Estate.hp = 0;
            m_text[0]->UpdateText("體力值:\n" + std::to_string(m_Estate.hp));

            if (m_Estate.hp > 0) {
                int Dm = std::max(0, m_Estate.atk - m_Pstate.def);
                m_Pstate.hp -= Dm;
                if (m_Pstate.hp < 0) m_Pstate.hp = 0;
                m_text[3]->UpdateText("體力值:\n" + std::to_string(m_Pstate.hp));
            }
            m_ActionCooldown = 20;
        }
    }
    else {
        if (m_timer > 15) m_timer = 15;
        else if (m_timer > 0) m_timer--;
        else {
            m_IsFinished = true;
            m_IsActive = false;
            SetVisible(false);
            for (int i = 0;i < 6; i++) { m_text[i]->SetVisible(false);}
            for (int i = 0;i < 3; i++) { m_text2[i]->SetVisible(false);}
            m_PlayerIcon->SetVisible(false);
            m_EnemyIcon->SetVisible(false);
        }
    }
}
