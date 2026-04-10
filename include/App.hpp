#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "BackgroundImage.hpp"
#include "Util/Renderer.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "UIText.hpp"
#include "FloorData.hpp"
#include "UIText/Toast.hpp"
#include "UIText/BattlePanel.hpp"
#include "UIText/ShopPanel.hpp"
#include "UIText/NPCDialog.hpp"
#include "UIText/FloorChangePanel.hpp"
#include "Block/Props.hpp"
#include "Block/Door.hpp"
#include "Block/Enemy.hpp"
#include "Block/NPC.hpp"
#include "Block/Shop.hpp"
#include "Util/Logger.hpp"
#include  <vector>
class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)
    void ChangeFloor(int floorDelta);
    bool JumpToFloor(int targetFloor);
    void ChangeRemoteBlock(int targetFloor, int x, int y, int newID);
private:
    void ValidTask();
    void ProcessPlayerMovement();
    void ProcessBattleResult();
    void ProcessShopLogic();
    void ProcessItemPickup(std::shared_ptr<Props> propsPtr);
    void ProcessNPCLogic();
    void ProcessFloorChange();

private:
    State m_CurrentState = State::START;
    std::vector<FloorData> m_FloorData;
    Util::Renderer m_Renderer;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Util::GameObject> m_PlayerIcon;
    std::vector<std::shared_ptr<UIText>> m_PlayerUI;
    std::shared_ptr<UIText> m_floorUI;
    std::vector<std::shared_ptr<UIText>> m_TryTextUI; //測試資料，需刪
    std::shared_ptr<Toast> m_Toast;
    std::shared_ptr<BattlePanel> m_BattlePanel;
    std::shared_ptr<ShopPanel> m_ShopPanel;
    std::shared_ptr<NPCDialog> m_NPCDialog;
    std::shared_ptr<FloorChangePanel> m_FloorChangePanel;
    int m_CurrentFloor = 0;
    std::shared_ptr<Enemy> m_CurrentEnemy = nullptr;
    std::shared_ptr<NPC> m_CurrentNPC = nullptr;
    // std::vector<std::shared_ptr<NPC>> m_NPCs;

    std::shared_ptr<Map> m_Map;
};

#endif

/*
git add .

git commit -m "更新內容說明"

git push
 */