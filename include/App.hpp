#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include <memory>

#include "Manager/GameFlowManager.hpp"

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

    std::vector<std::shared_ptr<Enemy>> GetEnemy();
    void HandleSystemInput();

    State m_CurrentState = State::START;

    std::shared_ptr<GameFlowManager> m_GameFlowManager;
};

#endif

/*
git add .

git commit -m "更新內容說明"

git push
 */