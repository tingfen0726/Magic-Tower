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
#include "Block/Props.hpp"
#include "Block/Door.hpp"
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

private:
    void ValidTask();
    void ProcessPlayerMovement();

private:
    State m_CurrentState = State::START;
    std::vector<FloorData> m_FloorData;
    Util::Renderer m_Renderer;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Player> m_Player;
    std::vector<std::shared_ptr<UIText>> m_PlayerUI;
    std::vector<std::shared_ptr<UIText>> m_TryTextUI; //測試資料，需刪
    std::shared_ptr<Toast> m_Toast;
    int m_CurrentFloor = 0;
    // std::vector<std::shared_ptr<NPC>> m_NPCs;
    // std::vector<std::shared_ptr<Enemies>> m_Enemies;

    std::shared_ptr<Map> m_Map;
};

#endif

/*
git add .

git commit -m "更新內容說明"

git push
 */