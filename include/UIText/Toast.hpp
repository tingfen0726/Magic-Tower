#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_TOAST_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_TOAST_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Toast : public Util::GameObject {
public:
    Toast(const std::string& text);
    void ShowToast(const std::string& prefix);
    void Update();
private:
    std::shared_ptr<UIText> m_text;
    int m_timer = 0;
};
#endif //REPLACE_WITH_YOUR_PROJECT_NAME_TOAST_HPP