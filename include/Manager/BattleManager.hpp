#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEMANAGER_HPP

#include "Player.hpp"
#include "Block/Enemy.hpp"
#include <functional>
#include <algorithm>
#include <string>

class BattleManager {
public:
    BattleManager(Player* player) : m_Player(player) {}

    std::function<void(int)> OnPlayerHpChanged;
    std::function<void(int)> OnEnemyHpChanged;
    std::function<void(bool)> OnBattleEnded;

    bool GetIsActive() const { return m_IsActive; }

    void StartBattle(EnemyStats enemyStats) {
        m_CurrentEnemy = enemyStats;
        m_IsActive = true;
        m_ActionCooldown = 10;

        if (OnPlayerHpChanged) OnPlayerHpChanged(m_Player->GetPlayerStats().hp);
        if (OnEnemyHpChanged) OnEnemyHpChanged(m_CurrentEnemy.hp);
    }

    void Update() {
        if (!m_IsActive) return;

        int playerHp = m_Player->GetPlayerStats().hp;

        if (playerHp > 0 && m_CurrentEnemy.hp > 0) {
            m_ActionCooldown--;
            if (m_ActionCooldown <= 0) {
                int p_level = m_Player->GetPlayerStats().level;
                int p_atk = m_Player->GetPlayerStats().atk;

                int critChance = std::min(100, static_cast<int>(p_level * 0.5f));
                bool isCrit = (rand() % 100) < critChance;
                int finalAtk = isCrit ? (p_atk * 2) : p_atk;
                int Dnorm = std::max(0, finalAtk - m_CurrentEnemy.def);

                m_CurrentEnemy.hp -= Dnorm;
                if (m_CurrentEnemy.hp < 0) m_CurrentEnemy.hp = 0;
                if (OnEnemyHpChanged) OnEnemyHpChanged(m_CurrentEnemy.hp);

                if (m_CurrentEnemy.hp > 0) {
                    int p_def = m_Player->GetPlayerStats().def;
                    int Dm = std::max(0, m_CurrentEnemy.atk - p_def);

                    m_Player->AddStats(PlayerLabel::Stat::HP, -Dm);
                    int newPlayerHp = m_Player->GetPlayerStats().hp;
                    if (newPlayerHp < 0) m_Player->SetStats(PlayerLabel::Stat::HP, 0);

                    if (OnPlayerHpChanged) OnPlayerHpChanged(m_Player->GetPlayerStats().hp);
                }
                m_ActionCooldown = 10;
            }
        }
        else {
            m_IsActive = false;
            bool playerWon = (m_Player->GetPlayerStats().hp > 0);

            if (OnBattleEnded) OnBattleEnded(playerWon);
        }
    }

private:
    Player* m_Player;
    EnemyStats m_CurrentEnemy;
    int m_ActionCooldown = 0;
    bool m_IsActive = false;
};
#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BATTLEMANAGER_HPP