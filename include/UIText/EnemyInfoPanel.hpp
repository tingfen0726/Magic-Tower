#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_ENEMYINFOPANEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_ENEMYINFOPANEL_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"
#include "Block/Enemy.hpp"
#include "Player.hpp"

struct EnemyStatsInfo {
    bool visible = false;
    std::vector<std::shared_ptr<UIText>> m_title;
    std::vector<std::shared_ptr<UIText>> m_stats;
    std::shared_ptr<Util::GameObject> m_enemyIcon;
    std::vector<std::string> m_enemyImages;
};

class EnemyInfoPanel : public Util::GameObject {
public:
    EnemyInfoPanel();
    void ShowEnemyInfoPanel(PlayerStats playerStats, std::vector<std::shared_ptr<Enemy>> enemies);
    // void ShowEnemyInfoPanel();
    void CloseEnemyInfoPanel();
    bool GetVisible() {return m_Visible;};
    void Update();
private:
    void SetInfo(PlayerStats playerStats, std::vector<std::shared_ptr<Enemy>> enemies);
    std::string GetName(int enemyID);
    bool m_Visible;

    PlayerStats m_playerStats;
    // std::vector<std::shared_ptr<Enemy>> m_enemies;
    std::vector<EnemyStatsInfo> m_enemies;
    std::vector<std::shared_ptr<Util::GameObject>> m_frames;

    unsigned int m_LastFrameTime = 0;
    int m_CurrentFrame = 0;

    const float IconstartX = -130.0f;
    const float IconstartY = 269.0f;
    const float IconintervalY = 77.0f;

    const float TextstartX = -60.0f;
    const float TextstartY = 282.0f;
    const float TextintervalY = 30.0f;
    const float TextintervalX = 190.0f;


};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_ENEMYINFOPANEL_HPP