#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "BackgroundImage.hpp"
#include "Util/Renderer.hpp"
#include "Player.hpp"
#include "Map.hpp"

#include "UIText/Toast.hpp"
#include "UIText/BattlePanel.hpp"
#include "UIText/ShopPanel.hpp"
#include "UIText/NPCDialog.hpp"
#include "UIText/FloorChangePanel.hpp"
#include "UIText/EnemyInfoPanel.hpp"
#include "UIText/GameClearPanel.hpp"

#include "Manager/ShopManager.hpp"
#include "Manager/BattleManager.hpp"
#include "Manager/LevelManager.hpp"
#include "Manager/ItemManager.hpp"
#include "Manager/NPCManager.hpp"
#include "Manager/MovementManager.hpp"
#include "Manager/UIManager.hpp"
#include "Manager/GameFlowManager.hpp"
#include "Manager/SaveManager.hpp"

#include "Block/Enemy.hpp"
#include <vector>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };
    enum class GameState {
        TITLE_SCREEN, // 標題畫面
        PLAYING,      // 遊玩中
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    std::vector<std::shared_ptr<Enemy>> GetEnemy();
    void HandleSystemInput();

    State m_CurrentState = State::START;
    GameState m_GameState = GameState::TITLE_SCREEN;

    Util::Renderer m_Renderer;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Util::GameObject> m_PlayerIcon;
    std::shared_ptr<Map> m_Map;

    // UI介面
    std::shared_ptr<Toast> m_Toast;
    std::shared_ptr<BattlePanel> m_BattlePanel;
    std::shared_ptr<ShopPanel> m_ShopPanel;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<FloorChangePanel> m_FloorChangePanel;
    std::shared_ptr<EnemyInfoPanel> m_EnemyInfoPanel;
    std::shared_ptr<GameClearPanel> m_GameClearPanel;

    // 經理部門
    std::shared_ptr<BattleManager> m_BattleManager;
    std::shared_ptr<LevelManager> m_LevelManager;
    std::shared_ptr<ItemManager> m_ItemManager;
    std::shared_ptr<NPCManager> m_NPCManager;
    std::shared_ptr<MovementManager> m_MovementManager;
    std::shared_ptr<UIManager> m_UIManager;
    std::shared_ptr<ShopManager> m_ShopManager;
    std::shared_ptr<GameFlowManager> m_GameFlowManager;
    std::shared_ptr<SaveManager> m_SaveManager;
};

#endif

/*
git add .

git commit -m "更新內容說明"

git push
 */