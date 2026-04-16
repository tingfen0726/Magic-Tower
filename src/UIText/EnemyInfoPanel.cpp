#include "UIText/EnemyInfoPanel.hpp"
#include "Util/Logger.hpp"
#include "GameConstants.hpp"
#include <string>

EnemyInfoPanel::EnemyInfoPanel() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/Black.bmp"));
    m_Transform.translation = {142.0f, 0};
    m_Transform.scale = {0.74, 0.74};
    SetZIndex(88);
    SetVisible(false);
    m_Visible = false;
    for (int i = 0; i < 8; i++) {
        auto frame = std::make_shared<Util::GameObject>();
        frame->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/EnemyFrame.bmp"));
        frame->m_Transform.translation = {IconstartX, IconstartY - i * IconintervalY};
        frame->m_Transform.scale = {0.7, 0.7};
        frame->SetZIndex(89);
        frame->SetVisible(false);
        AddChild(frame);
        m_frames.push_back(frame);
    }

    for (int i = 0; i < 8; i++) {
        EnemyStatsInfo enemystate;
        enemystate.visible = false;
        enemystate.m_enemyIcon = std::make_shared<Util::GameObject>();
        enemystate.m_enemyIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Road/lava.bmp"));
        enemystate.m_enemyIcon->m_Transform.translation = {IconstartX, IconstartY - i * IconintervalY};
        enemystate.m_enemyIcon->m_Transform.scale = {0.69, 0.69};
        enemystate.m_enemyIcon->SetZIndex(90);
        enemystate.m_enemyIcon->SetVisible(false);
        AddChild(enemystate.m_enemyIcon);

        std::vector<std::string> title= {"名稱", "體力", "攻擊", "防禦", "金・經", "損失"};
        for (int j = 0; j < 6; j++) {
            auto text = std::make_shared<UIText>(20, title[j], Util::Color{255,255,255,255}, 0, 0);
            text->SetZIndex(89);
            float currentBaseY = TextstartY - (i * IconintervalY);
            float offsetX = (j / 2) * TextintervalX;
            float offsetY = (j % 2) * TextintervalY;
            text->SetPosition(TextstartX + offsetX, currentBaseY - offsetY);
            text->SetVisible(false);
            AddChild(text);
            enemystate.m_title.push_back(text);
        }
        for (int j = 0; j < 6; j++) {
            std::string defaultText = (j == 0) ? "名字" : "1000";
            auto text = std::make_shared<UIText>(20, defaultText, Util::Color{255,255,255,255}, 0, 0);
            text->SetZIndex(89);
            float currentBaseY = TextstartY - (i * IconintervalY);
            float offsetX = (j / 2) * TextintervalX;
            float offsetY = (j % 2) * TextintervalY;
            text->SetPosition(TextstartX + offsetX + 90, currentBaseY - offsetY);
            text->SetVisible(false);
            AddChild(text);
            enemystate.m_stats.push_back(text);
        }
        // enemystate.m_state[4]->UpdateText("0・0");
        m_enemies.push_back(enemystate);
    }
}
void EnemyInfoPanel::ShowEnemyInfoPanel(PlayerStats playerStats, std::vector<std::shared_ptr<Enemy>> enemies) {
    SetVisible(true);
    m_Visible = true;
    for (int i = 0; i < enemies.size(); i++) {
        if (i >= m_enemies.size()) {
            LOG_WARN("該樓層怪物種類 ({}) 超過圖鑑顯示上限 ({})！", enemies.size(), m_enemies.size());
            break;
        }
        m_enemies[i].visible = true;
        m_frames[i]->SetVisible(true);
        m_enemies[i].m_enemyIcon->SetVisible(true);
        for (int j = 0; j < 6; j++) {
            m_enemies[i].m_stats[j]->SetVisible(true);
            m_enemies[i].m_title[j]->SetVisible(true);
        }
    }
    SetInfo(playerStats, enemies);
}

void EnemyInfoPanel::SetInfo(PlayerStats playerStats, std::vector<std::shared_ptr<Enemy>> enemies) {
    for (int i = 0; i < enemies.size(); i++) {
        EnemyStats enemy_stats = enemies[i]->GetEnemyStats();
        int predictedDamage =  playerStats.CalculateDamage(enemy_stats);
        std::string Loss =  (predictedDamage == 999999)? "???" : std::to_string(predictedDamage);
        m_enemies[i].m_stats[0]->UpdateText(GetName(enemies[i]->GetID()));
        m_enemies[i].m_stats[1]->UpdateText(std::to_string(enemy_stats.hp));
        m_enemies[i].m_stats[2]->UpdateText(std::to_string(enemy_stats.atk));
        m_enemies[i].m_stats[3]->UpdateText(std::to_string(enemy_stats.def));
        m_enemies[i].m_stats[4]->UpdateText(std::to_string(enemy_stats.gold) + "・" + std::to_string(enemy_stats.exp));
        m_enemies[i].m_stats[5]->UpdateText(Loss);

        m_enemies[i].m_enemyIcon->SetDrawable(std::make_shared<Util::Image>(enemies[i]->GetImagePath()[0]));
        m_enemies[i].m_enemyImages = enemies[i]->GetImagePath();
    }
}

std::string EnemyInfoPanel::GetName(int enemyID) {
    switch (enemyID) {
        case Config::ID::GREEN_SLIME:
            return "綠頭怪";
        case Config::ID::RED_SLIME:
            return "紅頭怪";
        case Config::ID::BAT:
            return "小蝙蝠";
        case Config::ID::SKELETON_C:
            return "骷髏人";
        case Config::ID::BIG_SLIME:
            return "青頭怪";
        case Config::ID::SKELETON_B:
            return "骷髏士兵";
        case Config::ID::PRIEST_C:
            return "初級法師";
        case Config::ID::BIG_BAT:
            return "大蝙蝠";
        case Config::ID::ZOMBIE:
            return "獸面人";
        case Config::ID::SKELETON_A:
            return "骷髏隊長";
        case Config::ID::STONE_MONSTER_B:
            return "石頭怪人";
        case Config::ID::MAGACIAN_B:
            return "麻衣法師";
        case Config::ID::GATE_KEEPER_C:
            return "初級衛兵";
        case Config::ID::RED_BAT:
            return "紅蝙蝠";
        case Config::ID::PRIEST_A:
            return "高級法師";
        case Config::ID::SLIME_LORD:
            return "怪王";
        case Config::ID::MAGIC_SERGEANT_D:
            return "白衣武士";
        case Config::ID::KNIGHT:
            return "金衛士";
        case Config::ID::MAGACIAN_A:
            return "紅衣法師";
        case Config::ID::ZOMBIE_KNIGHT:
            return "獸面武士";
        case Config::ID::GATE_KEEPER_B:
            return "冥衛兵";
        case Config::ID::GATE_KEEPER_A:
            return "高級衛兵";
        case Config::ID::SWORDSMAN:
            return "雙手劍士";
        case Config::ID::SOUL_SKELETON_KNIGHT:
            return "冥戰士";
        case Config::ID::IRON_KNIGHT_A:
            return "金隊長";
        case Config::ID::DARK_MAGICIAN_1:
        case Config::ID::DARK_MAGICIAN_2:
        case Config::ID::DARK_MAGICIAN_3:
            return "靈法師";
        case Config::ID::SOUL_SKELETON_1:
        case Config::ID::SOUL_SKELETON_2:
        case Config::ID::SOUL_SKELETON_3:
            return "冥隊長";
        case Config::ID::DARK_KNIGHT_1:
        case Config::ID::DARK_KNIGHT_2:
        case Config::ID::DARK_KNIGHT_3:
            return "靈武士";
        case Config::ID::MAGIC_SERGEANT_A_1:
        case Config::ID::MAGIC_SERGEANT_A_2:
        case Config::ID::MAGIC_SERGEANT_A_3:
            return "紅衣魔王";
        case Config::ID::SLIME_MEN:
            return "影子戰士";
        case Config::ID::VAMPIRE_1:
        case Config::ID::VAMPIRE_2:
        case Config::ID::VAMPIRE_3:
            return "冥靈魔王";
    }
    return "名字";
}

void EnemyInfoPanel::CloseEnemyInfoPanel() {
    SetVisible(false);
    m_Visible = false;
    for (int i = 0; i < m_enemies.size(); i++) {
        m_frames[i]->SetVisible(false);
        m_enemies[i].m_enemyIcon->SetVisible(false);
        m_enemies[i].visible = false;
        for (int j = 0; j < 6; j++) {
            m_enemies[i].m_stats[j]->SetVisible(false);
            m_enemies[i].m_title[j]->SetVisible(false);
        }
    }
}

void EnemyInfoPanel::Update() {
    if (!m_Visible) return;
    unsigned int currentTime = SDL_GetTicks();
    if (currentTime - m_LastFrameTime > 150) {
        m_CurrentFrame = (m_CurrentFrame + 1) % 2;
        for (int i = 0; i < m_enemies.size(); i++) {
            if (!m_enemies[i].visible) continue;
            m_enemies[i].m_enemyIcon->SetDrawable(std::make_shared<Util::Image>(m_enemies[i].m_enemyImages[m_CurrentFrame]));
            m_LastFrameTime = currentTime;
        }
    }
}
