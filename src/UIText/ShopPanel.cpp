#include "UIText/ShopPanel.hpp"
#include <string>
ShopPanel::ShopPanel() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/ShopDialog.bmp"));
    m_Transform.translation = {142.0f, 0};
    m_Transform.scale = {0.75, 0.75};
    SetZIndex(88);
    SetVisible(false);
    m_Visible = false;
    
    m_ShopIcon = std::make_shared<Util::GameObject>();
    m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/shop_1_2.BMP"));
    m_ShopIcon->m_Transform.translation = {27, 145};
    m_ShopIcon->m_Transform.scale = {0.7125, 0.7125};
    m_ShopIcon->SetZIndex(89);
    m_ShopIcon->SetVisible(false);
    AddChild(m_ShopIcon);

    std::string text = "想要增加你的能力嗎?\n如果你有25個金幣,你\n可以任意選擇一項";
    m_content = std::make_shared<UIText>(20, text, Util::Color{255,255,255,255}, 200, 125);
    m_content->SetZIndex(89);
    m_content->SetVisible(false);
    AddChild(m_content);

    std::vector<std::string> options = {"增加800點體力", "增加4點攻擊", "增加4點防禦", "離開商店"};
    for (int i = 0; i < options.size(); i++) {
        auto option = std::make_shared<UIText>(20, options[i], Util::Color{255,255,255,255}, 0, 0);
            option->SetPosition(startX, startY - i * interval);
            option->SetZIndex(89);
            m_optionText.push_back(option);
            option->SetVisible(false);
            AddChild(option);
    }
    m_optionText[m_ptr]->SetColor(Util::Color{255, 215, 0, 255});
    m_arrow = std::make_shared<Util::GameObject>();
    m_arrow->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/right_arrow_gray.png"));
    m_arrow->m_Transform.translation = {10.0f, -20};
    m_arrow->m_Transform.scale = {0.75, 0.75};
    m_arrow->SetZIndex(89);
    m_arrow->SetVisible(false);
    AddChild(m_arrow);

}

void ShopPanel::ChangeOptions() {
    if (m_MoveCooldown > 0) {
        m_MoveCooldown--;
        return;
    }
    if (!m_Visible) return;
    bool isMoved = false;
    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        if (m_ptr <= 0) { m_ptr = 3;}
        else { m_ptr--;}
        isMoved = true;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        if (m_ptr >= 3) { m_ptr = 0;}
        else { m_ptr++;}
        isMoved = true;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        ExecuteOption();
    }
    if (isMoved) {
        m_arrow->m_Transform.translation = {10.0f, -20.0f - (m_ptr * interval)};
        m_optionText[m_ptr]->SetColor(Util::Color{255, 215, 0, 255});
        for (int i = 0; i < m_optionText.size(); i++) {
            if (i != m_ptr) m_optionText[i]->SetColor(Util::Color{255, 255, 255, 255});
        }
        m_MoveCooldown = 8;
    }
}

void ShopPanel::ExecuteOption() {
    if (m_ptr == 3) {
        CloseShopPanel();
        return;
    }
    if (OnConfirmPurchase) {
        bool success = OnConfirmPurchase(m_currentShopID, m_ptr);

        if (!success) {
            m_tradeFail = true;
        } else {
            m_tradeFail = false;
        }
    }
}

void ShopPanel::ShowShopPanel(int shopID) {
    m_currentShopID = shopID;
    ResetShopPanel();
    m_MoveCooldown = 8;
    m_Visible = true;
    SetVisible(true);
    m_ShopIcon->SetVisible(true);
    m_content->SetVisible(true);
    m_arrow->SetVisible(true);
    for (int i = 0; i < m_optionText.size(); i++) {
        m_optionText[i]->SetVisible(true);
    }
    if (shopID >= Config::ID::SHOP_EVEMY_11 && shopID <= Config::ID::SHOP_EVEMY_12) {
        m_content->UpdateText("想要增加你的能力嗎?\n如果你有25個金幣,你\n可以任意選擇一項");
        std::vector<std::string> options = {"增加800點體力", "增加4點攻擊", "增加4點防禦", "離開商店"};
        for (int i = 0; i < m_optionText.size(); i++) {
            m_optionText[i]->UpdateText(options[i]);
        }
        m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/shop_1_2.BMP"));
        return;
    }
    if (shopID == Config::ID::SHOP_EXP_2) {
        m_content->UpdateText("你好，英勇的人類，只\n要你有足夠的經驗，我就\n可以讓你變得更強大");
        std::vector<std::string> options = {"提升一級 ( 100點 )", "增加5點攻擊 ( 30點 )", "增加5點防禦 (30點)", "離開商店"};
        for (int i = 0; i < m_optionText.size(); i++) {
            m_optionText[i]->UpdateText(options[i]);
        }
        m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/elder.BMP"));
        return;
    }
    if (shopID == Config::ID::SHOP_KEY_3) {
        m_content->UpdateText("相信你一定有特殊的需\n要，只要你有金幣，我就\n可以幫你");
        std::vector<std::string> options = {"購買1把黃鑰匙 ( $10 )", "購買1把藍鑰匙 ( $50 )", "購買1把紅鑰匙 ( $100 )", "離開商店"};
        for (int i = 0; i < m_optionText.size(); i++) {
            m_optionText[i]->UpdateText(options[i]);
        }
        m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/shopkeeper.BMP"));
        return;
    }
    if (shopID >= Config::ID::SHOP_EVEMY_40 && shopID <= Config::ID::SHOP_EVEMY_42) {
        m_content->UpdateText("想要增加你的能力嗎?\n如果你有100個金幣,你\n可以任意選擇一項");
        std::vector<std::string> options = {"增加4000點體力", "增加20點攻擊", "增加20點防禦", "離開商店"};
        for (int i = 0; i < m_optionText.size(); i++) {
            m_optionText[i]->UpdateText(options[i]);
        }
        m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/shop_1_2.BMP"));
        return;
    }
    if (shopID == Config::ID::SHOP_KEY_5) {
        m_content->UpdateText("喔，歡迎你的到來，如\n果你手裡缺少金幣，我可\n以幫你");
        std::vector<std::string> options = {"賣出1把黃鑰匙 ( $7 )", "賣出1把藍鑰匙 ( $35 )", "賣出1把紅鑰匙 ( $70 )", "離開商店"};
        for (int i = 0; i < m_optionText.size(); i++) {
            m_optionText[i]->UpdateText(options[i]);
        }
        m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/shopkeeper.BMP"));
        return;
    }
    if (shopID == Config::ID::SHOP_ELDER_6) {
        m_content->UpdateText("你好，英勇的人類，只\n要你有足夠的經驗，我就\n可以讓你變得更強大");
        std::vector<std::string> options = {"提升三級 ( 270點 )", "增加17點攻擊 ( 95點 )", "增加17點防禦 (95點 )", "離開商店"};
        for (int i = 0; i < m_optionText.size(); i++) {
            m_optionText[i]->UpdateText(options[i]);
        }
        m_ShopIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Shop/elder.BMP"));
        return;
    }
}

void ShopPanel::CloseShopPanel() {
    m_Visible = false;
    SetVisible(false);
    m_ShopIcon->SetVisible(false);
    m_content->SetVisible(false);
    m_arrow->SetVisible(false);
    for (int i = 0; i < m_optionText.size(); i++) {
        m_optionText[i]->SetVisible(false);
    }
}

void ShopPanel::ResetShopPanel() {
    m_ptr = 0;
    m_arrow->m_Transform.translation = {10.0f, -20.0f};
    for (int i = 0; i < m_optionText.size(); i++) {
        m_optionText[i]->SetColor(Util::Color{255, 255, 255, 255});
    }
    m_optionText[0]->SetColor(Util::Color{255, 215, 0, 255});
}

void ShopPanel::Update() {
}
