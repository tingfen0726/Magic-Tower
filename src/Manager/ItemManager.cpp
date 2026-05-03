#include "Manager/ItemManager.hpp"

ItemManager::ItemManager(std::shared_ptr<Player> player, std::shared_ptr<Toast> toast)
    : m_Player(player), m_Toast(toast) {

}

void ItemManager::ProcessItemPickup(std::shared_ptr<Props> propsPtr) {
        if (propsPtr->GetPickUp()) {
        return;
    }
    propsPtr->PickUp();
    switch (propsPtr->GetID()) {
        case Config::ID::YELLOW_KEY:
            m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
            m_Toast->ShowToast("獲得 黃鑰匙 x1");
            break;
        case Config::ID::BLUE_KEY:
            m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
            m_Toast->ShowToast("獲得 藍鑰匙 x1");
            break;
        case Config::ID::RED_KEY:
            m_Player->AddKey(PlayerLabel::Key::RED, 1);
            m_Toast->ShowToast("獲得 紅鑰匙 x1");
            break;
        case Config::ID::MAGIC_KEY:
            m_Player->AddKey(PlayerLabel::Key::YELLOW, 1);
            m_Player->AddKey(PlayerLabel::Key::BLUE, 1);
            m_Player->AddKey(PlayerLabel::Key::RED, 1);
            m_Toast->ShowToast("獲得 鑰匙盒 各種鑰匙數 x1");
            break;
        case Config::ID::RED_POTION:
            m_Player->AddStats(PlayerLabel::Stat::HP, 200);
            m_Toast->ShowToast("獲得 小血瓶 體力 +200");
            break;
        case Config::ID::BLUE_POTION:
            m_Player->AddStats(PlayerLabel::Stat::HP, 500);
            m_Toast->ShowToast("獲得 大血瓶 體力 +500");
            break;
        case Config::ID::HOLY_WATER:
            m_Player->SetStats(PlayerLabel::Stat::HP, m_Player->GetPlayerStats().hp * 2);
            m_Toast->ShowToast("獲得 聖水 當前體力翻倍");
            break;
        case Config::ID::RUBY:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 3);
            m_Toast->ShowToast("獲得 紅色寶石 攻擊力 +3");
            break;
        case Config::ID::SAPPHIRE:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 3);
            m_Toast->ShowToast("獲得 藍色寶石 防禦力 +3");
            break;
        case Config::ID::SWORD_B:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 150);
            m_Toast->ShowToast("獲得 星光神劍 攻擊力 +150");
            break;
        case Config::ID::SWORD_C:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 70);
            m_Toast->ShowToast("獲得 青峰劍 攻擊力 +70");
            break;
        case Config::ID::SWORD_D:
            m_Player->AddStats(PlayerLabel::Stat::ATK, 10);
            m_Toast->ShowToast("獲得 鐵劍 攻擊力 +10");
            break;
        case Config::ID::SHIELD_A:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 190);
            m_Toast->ShowToast("獲得 光芒神盾 防禦力 +190");
            break;
        case Config::ID::SHIELD_C:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 10);
            m_Toast->ShowToast("獲得 鐵盾 防禦力 +10");
            break;
        case Config::ID::SHIELD_D:
            m_Player->AddStats(PlayerLabel::Stat::DEF, 85);
            m_Toast->ShowToast("獲得 黃金盾 防禦力 +85");
            break;
        case Config::ID::COIN:
            m_Player->AddStats(PlayerLabel::Stat::GOLD, 300);
            m_Toast->ShowToast("獲得 金塊 金幣 +300");
            break;
        case Config::ID::JUMP_WING_SMALL:
            m_Player->AddStats(PlayerLabel::Stat::LEVEL, 1);
            m_Toast->ShowToast("獲得 小飛羽 等級 +1");
            break;
        case Config::ID::JUMP_WING_BIG:
            m_Player->AddStats(PlayerLabel::Stat::LEVEL, 3);
            m_Toast->ShowToast("獲得 大飛羽 等級 +3");
            break;
        case Config::ID::HOLY_CROSS:
            m_Player->SetItem(PlayerLabel::Item::HOLYCROSS, true);
            m_Toast->ShowToast("獲得 神聖十字架 提升體功防屬性");
            break;
        case Config::ID::RED_VERI:
            m_Player->SetItem(PlayerLabel::Item::REDVERI, true);
            m_Toast->ShowToast("獲得 炎之靈杖");
            break;
        case Config::ID::GREEN_VERI:
            m_Player->SetItem(PlayerLabel::Item::GREENVERI, true);
            m_Toast->ShowToast("獲得 心之靈杖");
            break;
        case Config::ID::GEM_HOE:
            m_Player->SetItem(PlayerLabel::Item::GEMHOE, true);
            m_Toast->ShowToast("獲得 紅寶石榔頭");
            break;
        case Config::ID::GOD_KNIFE_SIGN:
            m_Player->SetItem(PlayerLabel::Item::GODKNIFESIGN, true);
            m_Toast->ShowToast("獲得 聖光徽");
            break;
        case Config::ID::WIND_COMPASS:
            m_Player->SetItem(PlayerLabel::Item::WINDCOMPASS, true);
            m_Toast->ShowToast("獲得 風之羅盤");
            break;
        default:
            break;
    }
}