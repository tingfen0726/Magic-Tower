#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_UIMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_UIMANAGER_HPP

#include <memory>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Util/Renderer.hpp"
#include "UIText.hpp"
#include "LevelManager.hpp"

class UIManager {
public:
    UIManager(std::shared_ptr<Player> player, std::shared_ptr<LevelManager> levelManager, Util::Renderer& renderer);

    void UpdateHUD();

    void SetHUDVisible(bool visible);

private:
    std::shared_ptr<Player> m_Player;

    std::vector<std::shared_ptr<UIText>> m_PlayerUI;
    std::vector<std::shared_ptr<UIText>> m_TryTextUI;
    std::shared_ptr<UIText> m_floorUI;
    std::shared_ptr<LevelManager> m_LevelManager;
};


#endif //REPLACE_WITH_YOUR_PROJECT_NAME_UIMANAGER_HPP