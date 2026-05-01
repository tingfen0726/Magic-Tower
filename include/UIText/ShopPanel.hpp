#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SHOPPANEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SHOPPANEL_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"
#include "Player.hpp"
#include "GameConstants.hpp"

class ShopPanel : public Util::GameObject {
public:
    ShopPanel();
    void ChangeOptions();
    void Update();
    void ShowShopPanel(int shopID);
    bool GetVisible() {return m_Visible;};
    bool GetTradeFail() {return m_tradeFail;};
    void ResetTradeFail() {m_tradeFail = false;};

    std::function<bool(int shopID, int optionIndex)> OnConfirmPurchase;
private:
    void CloseShopPanel();
    void ExecuteOption();
    void ResetShopPanel();

    std::shared_ptr<UIText> m_content;
    std::vector<std::shared_ptr<UIText>> m_optionText;

    std::shared_ptr<Util::GameObject> m_ShopIcon;
    std::shared_ptr<Util::GameObject> m_arrow;

    int m_ptr = 0;
    int m_MoveCooldown = 0;
    bool m_Visible;
    int m_currentShopID = 0; // 哪間店

    const float startX = 150.0f;
    const float startY = -20.0f;
    const float interval = 50.0f;
    bool m_tradeFail = false;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SHOPPANEL_HPP