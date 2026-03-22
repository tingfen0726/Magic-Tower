#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PLAYERSTATUI_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PLAYERSTATUI_HPP

#include "UIText.hpp"

class PlayerStatUI : public UIText {
public:
    PlayerStatUI(const std::string& fontPath, int fontSize, const std::string& text, const Util::Color& color, int x, int y);
    void UpdateValue(const std::string& prefix, int value) override;
private:
    std::string m_Prefix;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PLAYERSTATUI_HPP