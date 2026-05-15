#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GAMECLEARPANEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GAMECLEARPANEL_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"

class GameClearPanel : public Util::GameObject {
public:
    GameClearPanel();
    void ShowGameClearPanel();
    bool GetVisible() {return m_Visible;};
    void Update();
private:
    std::shared_ptr<UIText> m_text;
    std::shared_ptr<UIText> m_EscText;
    bool m_Visible = false;
    bool m_IsFinished = false;
    bool m_IsHighOpacity = false;
    bool m_IsDelaying = false;

    int m_LastBlinkTime = 0;
    int m_LastFrameTime = 0;
    int m_StartTime = 0;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GAMECLEARPANEL_HPP