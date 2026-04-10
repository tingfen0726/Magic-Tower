#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_FLOORCHANGEPANEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_FLOORCHANGEPANEL_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"
#include "Player.hpp"

class FloorChangePanel : public Util::GameObject {
public:
    FloorChangePanel();
    void ShowFloorChangePanel(bool Bool);
    bool GetVisible() {return m_Visible;};
    int ChangeOptions();
    void Update();
private:
    void CloseFloorChangePanel();
    void ExecuteOption();
    void ResetShopPanel();
    bool m_Visible;
    std::shared_ptr<UIText> m_Title;
    std::vector<std::shared_ptr<UIText>> m_Floors;
    std::shared_ptr<UIText> m_SpaceText;
    std::shared_ptr<Util::GameObject> m_arrow;
    int m_ptr = 0;

    unsigned int m_LastBlinkTime = 0;
    bool m_IsHighOpacity = true;
    int m_MoveCooldown = 0;

    const float startX = 20.0f;
    const float startY = 90.0f;
    const float intervalY = 45.0f;
    const float intervalX = 130.0f;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FLOORCHANGEPANEL_HPP