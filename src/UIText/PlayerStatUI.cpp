#include "UIText/PlayerStatUI.hpp"

PlayerStatUI::PlayerStatUI(const std::string &fontPath, int fontSize, const std::string &text, const Util::Color &color, int x, int y) : UIText(fontPath, fontSize, text, color, x, y) {


}

void PlayerStatUI::UpdateValue(const std::string &prefix, int value) {
    auto textDrawable = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
    if (textDrawable) {
        textDrawable->SetText(std::to_string(value));
    }
}
