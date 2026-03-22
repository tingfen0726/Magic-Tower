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
    UIText(const std::string& fontPath, int fontSize, const std::string& text, const Util::Color& color, int x, int y) {
        m_Drawable = std::make_shared<Util::Text>(fontPath, fontSize, text, color);
        SetZIndex(100);
        m_Transform.translation = {x, y};
    }
    virtual void UpdateValue(const std::string& prefix, int value) = 0;
    void SetPosition(float x, float y) { m_Transform.translation = {x, y};}
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_UITEXT_HPP