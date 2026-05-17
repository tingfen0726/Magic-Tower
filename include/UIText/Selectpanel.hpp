#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SELECTPANEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SELECTPANEL_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"

class Selectpanel : public Util::GameObject {
public:
    Selectpanel();
    void ShowSelectpanel(std::vector<std::string> filenames);
    void CloseSelectpanel();
    bool GetVisible() {return m_Visible;};
    std::string ChangeOptions();
    void Update();
private:
    std::string FormatSaveTimeForUI(const std::string& filename);
    void ResetShopPanel();
    bool m_Visible;
    std::shared_ptr<UIText> m_Title;
    std::vector<std::shared_ptr<UIText>> m_datas;
    std::shared_ptr<UIText> m_SpaceText;
    std::shared_ptr<Util::GameObject> m_arrow;
    std::vector<std::string> m_filenames;
    int m_ptr = 0;

    unsigned int m_LastBlinkTime = 0;
    bool m_IsHighOpacity = true;
    int m_MoveCooldown = 0;

    const float startX = 150.0f;
    const float startY = 28.0f;
    const float intervalY = 45.0f;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SELECTPANEL_HPP