#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SHOPMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SHOPMANAGER_HPP

#include "../Player.hpp"

class ShopManager {
public:
    ShopManager(Player* player) : m_Player(player) {}

    bool ProcessPurchase(int shopID, int optionIndex) {

        if (shopID >= Config::ID::SHOP_EVEMY_10 && shopID <= Config::ID::SHOP_EVEMY_12) {
            if (m_Player->GetPlayerStats().gold < 25) return false;
            m_Player->AddStats(PlayerLabel::Stat::GOLD, -25);
            if (optionIndex == 0) m_Player->AddStats(PlayerLabel::Stat::HP, 800);
            if (optionIndex == 1) m_Player->AddStats(PlayerLabel::Stat::ATK, 4);
            if (optionIndex == 2) m_Player->AddStats(PlayerLabel::Stat::DEF, 4);
            return true;
        }
        if (shopID == Config::ID::SHOP_EXP_2) {
            if (optionIndex == 0) {
                if (m_Player->GetPlayerStats().exp < 100) return false;
                m_Player->AddStats(PlayerLabel::Stat::EXP, -100);
                m_Player->AddStats(PlayerLabel::Stat::LEVEL, 1);
                return true;
            }
            if (optionIndex == 1) {
                if (m_Player->GetPlayerStats().exp < 30) return false;
                m_Player->AddStats(PlayerLabel::Stat::EXP, -30);
                m_Player->AddStats(PlayerLabel::Stat::ATK, 5);
                return true;
            }
            if (optionIndex == 2) {
                if (m_Player->GetPlayerStats().exp < 30) return false;
                m_Player->AddStats(PlayerLabel::Stat::EXP, -30);
                m_Player->AddStats(PlayerLabel::Stat::DEF, 5);
                return true;
            }
        }
        if (shopID == Config::ID::SHOP_KEY_3) {
            if (optionIndex == 0) {
                if (m_Player->GetPlayerStats().gold < 10) return false;
                m_Player->AddStats(PlayerLabel::Stat::GOLD, -10);
                m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
                return true;
            }
            if (optionIndex == 1) {
                if (m_Player->GetPlayerStats().gold < 50) return false;
                m_Player->AddStats(PlayerLabel::Stat::GOLD, -50);
                m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
                return true;
            }
            if (optionIndex == 2) {
                if (m_Player->GetPlayerStats().gold < 100) return false;
                m_Player->AddStats(PlayerLabel::Stat::GOLD, -100);
                m_Player->AddKey(PlayerLabel::Key::RED, 1);
                return true;
            }
        }
        if (shopID >= Config::ID::SHOP_EVEMY_40 && shopID <= Config::ID::SHOP_EVEMY_42) {
            if (m_Player->GetPlayerStats().gold < 100) return false;
            m_Player->AddStats(PlayerLabel::Stat::GOLD, -100);
            if (optionIndex == 0) m_Player->AddStats(PlayerLabel::Stat::HP, 4000);
            if (optionIndex == 1) m_Player->AddStats(PlayerLabel::Stat::ATK, 20);
            if (optionIndex == 2) m_Player->AddStats(PlayerLabel::Stat::DEF, 20);
            return true;
        }
        if (shopID == Config::ID::SHOP_KEY_5) {
            if (optionIndex == 0) {
                if (m_Player->GetInventory().yellowKey < 1) return false;
                m_Player->AddKey(PlayerLabel::Key::YELLOW, -1);
                m_Player->AddStats(PlayerLabel::Stat::GOLD, 7);
                return true;
            }
            if (optionIndex == 1) {
                if (m_Player->GetInventory().blueKey < 1) return false;
                m_Player->AddKey(PlayerLabel::Key::BLUE, -1);
                m_Player->AddStats(PlayerLabel::Stat::GOLD, 35);
                return true;
            }
            if (optionIndex == 2) {
                if (m_Player->GetInventory().redKey < 1) return false;
                m_Player->AddKey(PlayerLabel::Key::RED, -1);
                m_Player->AddStats(PlayerLabel::Stat::GOLD, 70);
                return true;
            }
        }
        if (shopID == Config::ID::SHOP_ELDER_6) {
            if (optionIndex == 0) {
                if (m_Player->GetPlayerStats().exp < 270) return false;
                m_Player->AddStats(PlayerLabel::Stat::EXP, -270);
                m_Player->AddStats(PlayerLabel::Stat::LEVEL, 3);
                return true;
            }
            if (optionIndex == 1) {
                if (m_Player->GetPlayerStats().exp < 95) return false;
                m_Player->AddStats(PlayerLabel::Stat::EXP, -95);
                m_Player->AddStats(PlayerLabel::Stat::ATK, 17);
                return true;
            }
            if (optionIndex == 2) {
                if (m_Player->GetPlayerStats().exp < 95) return false;
                m_Player->AddStats(PlayerLabel::Stat::EXP, -95);
                m_Player->AddStats(PlayerLabel::Stat::DEF, 17);
                return true;
            }
        }
        return false;
    }

private:
    Player* m_Player;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SHOPMANAGER_HPP