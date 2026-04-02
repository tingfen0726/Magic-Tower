#include "UIText/Toast.hpp"

Toast::Toast(const std::string &text){
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Item/itemDialog.bmp"));
    m_Transform.translation = {0, 0};
    SetZIndex(98);
    m_text = std::make_shared<UIText>(36, text, Util::Color{255,255,255,255}, 0, 0);
    m_text->SetZIndex(99);
    AddChild(m_text);
}

void Toast::ShowToast(const std::string &prefix) {
    m_text->UpdateText(prefix);
    SetVisible(true);
    m_text->SetVisible(true);
    m_timer = 15;
}

void Toast::Update() {
    if (m_timer > 0) {
        m_timer--;
    }
    if (m_timer == 0) {
        SetVisible(false);
        m_text->SetVisible(false);
        m_text->SetColor(Util::Color{255,255,255,255});
    }
}
