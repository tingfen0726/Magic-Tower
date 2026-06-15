#include "UIText/GameClearPanel.hpp"
#include "Util/Image.hpp"
#include <string>


GameClearPanel::GameClearPanel() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Scene/GameOver.bmp"));
    m_Transform.translation = {0, 0};
    SetZIndex(70);
    SetVisible(false);

    std::string text = "　大魔頭被殺死了，公主也被救出了塔，蝶仙\n"
                       "的精力也恢復了。　　　　　　　　　　　　\n"
                       "　當勇士和公主一起走出塔來的時候，國王也\n"
                       "帶著軍隊來到了島外。　　　　　　　　　　\n"
                       "　一切都是那麼的平常。　　　　　　　　　\n"
                       "　回國後，國王為勇士和公主舉行了隆重而且\n"
                       "盛大的婚禮，並且宣布由勇士來繼承國王的位\n"
                       "置。從此之後，勇士和公主就幸福的生活在一\n"
                       "起了。　　　　　　　　　　　　　　　　　\n";


    m_text = std::make_shared<UIText>(46, text, Util::Color{255, 255, 255, 255}, 0, -600.0f);
    m_text->SetZIndex(72);
    m_text->SetVisible(false);
    AddChild(m_text);

    m_EscText = std::make_shared<UIText>(46, " 按 Esc 離開遊戲", Util::Color{255, 255, 255, 255}, 0, 0);
    m_EscText ->SetZIndex(72);
    m_EscText ->SetVisible(false);
    AddChild(m_EscText );
}

void GameClearPanel::ShowGameClearPanel() {
    m_Visible = true;

    m_StartTime = SDL_GetTicks();
    m_IsDelaying = true;
}

void GameClearPanel::Update() {
    if (!GetVisible()) return;
    unsigned int currentTime = SDL_GetTicks();
    if (m_IsDelaying) {
        if (currentTime - m_StartTime > 1000) {
            m_IsDelaying = false;
            SetVisible(true);
            m_text->SetVisible(true);
            m_LastFrameTime = currentTime;
        }
        return;
    }
    if (currentTime - m_LastFrameTime > 16) {

        if (m_text->m_Transform.translation.y < 600.0f) {
            m_text->m_Transform.translation.y += 1.0f;
        }
        else {
            m_IsFinished = true;
        }
        m_LastFrameTime = currentTime;
    }
    if (!m_IsFinished) return;
    m_EscText->SetVisible(true);
    if (currentTime - m_LastBlinkTime > 250) {

        m_IsHighOpacity = !m_IsHighOpacity;

        if (m_IsHighOpacity) {
            m_EscText->SetColor(Util::Color{255, 255, 255, 255});
        } else {
            m_EscText->SetColor(Util::Color{255, 255, 255, 150});
        }
        m_LastBlinkTime = currentTime;
    }
}

