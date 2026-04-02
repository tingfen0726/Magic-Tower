//
// Created by fenfenfen on 2026/3/22.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_UITEXT_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_UITEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include <string>

class UIText : public Util::GameObject {
public:
    UIText(int fontSize, const std::string& text, const Util::Color& color, int x, int y) {
        m_TextComponent = std::make_shared<Util::Text>(RESOURCE_DIR "/Font/Cubic_11_1.010_R.ttf", fontSize, text, color);
        m_Drawable = m_TextComponent;
        SetZIndex(80);
        m_Transform.translation = {x, y};
    }
    virtual void UpdateValue(int value) {
        if (m_TextComponent) m_TextComponent->SetText(std::to_string(value));
    };

    virtual void UpdateText(const std::string& text) {
        if (m_TextComponent) m_TextComponent->SetText(text);
    }

    virtual void UpdateTextValue(const std::string& prefix, int value) {
        if (m_TextComponent) m_TextComponent->SetText(prefix + std::to_string(value));
    }
    virtual void UpdateValueText(const std::string& prefix, int value) {
        if (m_TextComponent) m_TextComponent->SetText(std::to_string(value) + prefix);
    }
    void SetColor(const Util::Color& color) { m_TextComponent->SetColor(color); }
    void SetPosition(float x, float y) { m_Transform.translation = {x, y};}
private:
    std::shared_ptr<Util::Text> m_TextComponent;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_UITEXT_HPP