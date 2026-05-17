#include "Manager/BattleManager.hpp"
#include <algorithm>
#include <string>

BattleManager::BattleManager(Player* player, std::shared_ptr<Toast> toast)
        : m_Player(player), m_Toast(toast) {

}

bool BattleManager::TryStartBattle(PlayerStats playerStats, EnemyStats enemyStats) {
    if (playerStats.CalculateDamage(enemyStats) >= playerStats.hp) {
        m_Toast->SetColor(Util::Color{180, 0, 0, 255});
        m_Toast->ShowToast("你打不過此怪物！");
        return false;
    }

    StartBattle(enemyStats);
    return true;
}

void BattleManager::StartBattle(EnemyStats enemyStats) {
    m_CurrentEnemy = enemyStats;
    m_IsActive = true;
    m_IsEnding = false;
    m_ActionCooldown = 10;

    int currentHp = m_Player->GetPlayerStats().hp;
    int initialLoss = 0;

    if (m_CurrentEnemy.loss > 0 && m_CurrentEnemy.loss < 1) {
        initialLoss = static_cast<int>(m_CurrentEnemy.loss * currentHp);
    }
    else if (m_CurrentEnemy.loss >= 1) {
        initialLoss = static_cast<int>(m_CurrentEnemy.loss);
    }

    if (initialLoss > 0) {
        m_Player->AddStats(PlayerLabel::Stat::HP, -initialLoss);
        if (m_Player->GetPlayerStats().hp < 0) {
            m_Player->SetStats(PlayerLabel::Stat::HP, 0);
        }
    }
    if (OnPlayerHpChanged) OnPlayerHpChanged(m_Player->GetPlayerStats().hp);
    if (OnEnemyHpChanged) OnEnemyHpChanged(m_CurrentEnemy.hp);
}

void BattleManager::Update() {
    if (!m_IsActive) return;

    int playerHp = m_Player->GetPlayerStats().hp;

    if (playerHp > 0 && m_CurrentEnemy.hp > 0) {
        m_ActionCooldown--;
        if (m_ActionCooldown <= 0) {
            int p_level = m_Player->GetPlayerStats().level;
            int p_atk = m_Player->GetPlayerStats().atk;

            int critChance = std::min(100, static_cast<int>(p_level * 0.5f));
            bool isCrit = (rand() % 100) < critChance;

            int baseDamage = std::max(0, p_atk - m_CurrentEnemy.def);
            int Dnorm = isCrit ? (baseDamage * 2) : baseDamage;
            if (isCrit) m_Toast->ShowToast(std::to_string(Dnorm));

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
        // 如果還沒進入結算狀態，就初始化它
        if (!m_IsEnding) {
            m_IsEnding = true;
            m_EndCooldown = 15;
            bool playerWon = (playerHp > 0);
            if (playerWon) {
                if (OnShowVictoryHint) OnShowVictoryHint();
            }
        }
        else {
            m_EndCooldown--;
            if (m_EndCooldown <= 0) {
                m_IsActive = false;
                m_IsEnding = false;

                bool playerWon = (playerHp > 0);
                if (OnBattleEnded) {
                    OnBattleEnded(playerWon);
                    if (playerWon) {
                        m_Toast->ShowToast("獲得 金幣數 " + std::to_string(m_CurrentEnemy.gold) + " 經驗值 " + std::to_string(m_CurrentEnemy.exp) + "!");
                    }
                }
            }
        }
    }
}