#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "BackgroundImage.hpp"
#include "Util/Renderer.hpp"
#include "Player.hpp"
#include "Map.hpp"
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

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    Util::Renderer m_Renderer;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Player> m_Player;
    // std::vector<std::shared_ptr<NPC>> m_NPCs;
    // std::vector<std::shared_ptr<Character>> m_Enemies;

    std::shared_ptr<Map> m_Map;
};

#endif
