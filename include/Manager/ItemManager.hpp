#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_ITEMMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_ITEMMANAGER_HPP

#include <memory>
#include "Player.hpp"
#include "UIText/Toast.hpp" // 請確認你的 Toast 標頭檔路徑
#include "Block/Props.hpp"

class ItemManager {
public:
    ItemManager(std::shared_ptr<Player> player, std::shared_ptr<Toast> toast);

    void ProcessItemPickup(std::shared_ptr<Props> propsPtr);

private:
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Toast> m_Toast;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_ITEMMANAGER_HPP