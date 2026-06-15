#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GAMEFLOWMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GAMEFLOWMANAGER_HPP

#include <memory>
#include <vector>
#include <string>

// 系統與畫面
#include "Util/Renderer.hpp"
#include "GameSaveData.hpp"
class BackgroundImage;

// 實體物件
class Player;
class Map;
class Enemy;

// UI 介面
class Toast;
class BattlePanel;
class ShopPanel;
class NPCDialog;
class FloorChangePanel;
class EnemyInfoPanel;
class GameClearPanel;
class Selectpanel;

class ShopManager;
class BattleManager;
class LevelManager;
class ItemManager;
class NPCManager;
class MovementManager;
class UIManager;
class SaveManager;

// 資料結構


class GameFlowManager {
public:
    enum class GameState {
        TITLE_SCREEN, // 標題畫面
        PLAYING,      // 遊玩中
    };

    GameFlowManager();

    void Initialize();

    bool IsPlayerLockedByUI();
    void ProcessBattleResult(bool isWin);
    void ProcessShopLogic();
    void ProcessFloorChange();
    void ProcessLoadData();

    std::vector<std::shared_ptr<Enemy>> GetEnemy();
    void HandleSystemInput();

    void SetCurrentEnemy(std::shared_ptr<Enemy> enemy) { m_CurrentEnemy = enemy; }
    std::shared_ptr<Enemy> GetCurrentEnemy() { return m_CurrentEnemy; }

    void RestoreGameState(const GameSaveData& data);
    void ResetGame();
    void LoadGame(const std::string& filename);

    void Update();

private:
    Util::Renderer m_Renderer;
    GameState m_GameState = GameState::TITLE_SCREEN;

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
    std::shared_ptr<Selectpanel> m_Selectpanel;

    // 經理部門
    std::shared_ptr<BattleManager> m_BattleManager;
    std::shared_ptr<LevelManager> m_LevelManager;
    std::shared_ptr<ItemManager> m_ItemManager;
    std::shared_ptr<NPCManager> m_NPCManager;
    std::shared_ptr<MovementManager> m_MovementManager;
    std::shared_ptr<UIManager> m_UIManager;
    std::shared_ptr<ShopManager> m_ShopManager;

    std::shared_ptr<SaveManager> m_SaveManager;

    std::shared_ptr<Enemy> m_CurrentEnemy = nullptr;
};



#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GAMEFLOWMANAGER_HPP