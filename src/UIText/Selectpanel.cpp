#include "UIText/Selectpanel.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include <string>

Selectpanel::Selectpanel() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/Black.bmp"));
    m_Transform.translation = {142.0f, 0};
    m_Transform.scale = {0.5, 0.25};
    SetZIndex(40);
    SetVisible(false);
    m_Visible = false;

    m_Title = std::make_shared<UIText>(28, "- - 遊戲紀錄 - -", Util::Color{255,255,255,255}, 150, 75);
    m_Title->SetZIndex(42);
    m_Title->SetVisible(false);
    AddChild(m_Title);

    for (int i = 0; i < 3; i++) {
        auto data = std::make_shared<UIText>(22, "2026/01/01 00:00:00", Util::Color{255,255,255,255}, 0, 0);
        data->SetZIndex(42);
        data->SetPosition(startX, startY - (i) * intervalY);
        data->SetVisible(false);
        AddChild(data);
        m_datas.push_back(data);
    }
    m_SpaceText = std::make_shared<UIText>(16, "~~space~~", Util::Color{255,255,255,255}, 308, -87);
    m_SpaceText->SetZIndex(42);
    m_SpaceText->SetVisible(false);
    AddChild(m_SpaceText);

    m_datas[m_ptr]->SetColor(Util::Color{255, 215, 0, 255});
    m_arrow = std::make_shared<Util::GameObject>();
    m_arrow->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/right_arrow_gray.png"));
    m_arrow->m_Transform.translation = {startX - 150, startY};
    m_arrow->m_Transform.scale = {0.65, 0.65};
    m_arrow->SetZIndex(42);
    m_arrow->SetVisible(false);
    AddChild(m_arrow);
}

void Selectpanel::ShowSelectpanel(std::vector<std::string> filenames) {
    m_filenames = filenames;

    ResetShopPanel();
    SetVisible(true);
    m_Visible = true;
    m_Title->SetVisible(true);
    for (auto data : m_datas) { data->SetVisible(true); }
    m_SpaceText->SetVisible(true);
    m_arrow->SetVisible(true);
    m_MoveCooldown = 8;

    for (int i = 0; i < m_datas.size(); i++) {
        if (i < m_filenames.size()) {
            std::string dataname = FormatSaveTimeForUI(m_filenames[i]);
            m_datas[i]->UpdateText(dataname);
        } else {
            m_datas[i]->UpdateText("[ 尚 無 紀 錄 ]");
        }
    }

}

void Selectpanel::CloseSelectpanel() {
    SetVisible(false);
    m_Visible = false;
    m_Title->SetVisible(false);
    for (auto data : m_datas) { data->SetVisible(false); }
    m_SpaceText->SetVisible(false);
    m_arrow->SetVisible(false);
}

std::string Selectpanel::ChangeOptions() {

    if (!m_Visible) return "";
    if (m_MoveCooldown > 0) {
        m_MoveCooldown--;
        return "";
    }

    bool isMoved = false;
    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        if (m_ptr <= 0) { m_ptr = 2;}
        else { m_ptr--;}
        isMoved = true;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        if (m_ptr >= 2) { m_ptr = 0;}
        else { m_ptr++;}
        isMoved = true;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        CloseSelectpanel();
        if (m_ptr < m_filenames.size()) {
            return m_filenames[m_ptr];
        }
        return "";
    }

    if (isMoved) {
        m_arrow->m_Transform.translation = {startX - 150.0f, startY - (m_ptr) * intervalY};

        m_datas[m_ptr]->SetColor(Util::Color{255, 215, 0, 255});
        for (int i = 0; i < m_datas.size(); i++) {
            if (i != m_ptr) m_datas[i]->SetColor(Util::Color{255, 255, 255, 255});
        }
        m_MoveCooldown = 8;
    }
    return "";
}

void Selectpanel::ResetShopPanel() {
    m_ptr = 0;
    m_arrow->m_Transform.translation = {startX - 150, startY};
    for (int i = 0; i < m_datas.size(); i++) {
        m_datas[i]->SetColor(Util::Color{255, 255, 255, 255});
    }
    m_datas[0]->SetColor(Util::Color{255, 215, 0, 255});
}

std::string Selectpanel::FormatSaveTimeForUI(const std::string& filename) {
    size_t startPos = filename.find("Save_");

    if (startPos == std::string::npos || filename.length() - startPos < 19) {
        return filename;
    }
    std::string year   = filename.substr(startPos + 5, 4);
    std::string month  = filename.substr(startPos + 9, 2);
    std::string day    = filename.substr(startPos + 11, 2);
    std::string hour   = filename.substr(startPos + 14, 2);
    std::string minute = filename.substr(startPos + 16, 2);
    std::string second = filename.substr(startPos + 18, 2);

    std::string readableTime = year + "/" + month + "/" + day + " " + hour + ":" + minute + ":" + second;

    return readableTime;
}

void Selectpanel::Update() {
    if (!m_Visible) return;

    unsigned int currentTime = SDL_GetTicks();
    if (currentTime - m_LastBlinkTime > 150) {

        m_IsHighOpacity = !m_IsHighOpacity;

        if (m_IsHighOpacity) {
            m_SpaceText->SetColor(Util::Color{255, 255, 255, 255});
        } else {
            m_SpaceText->SetColor(Util::Color{255, 255, 255, 150});
        }
        m_LastBlinkTime = currentTime;
    }
}
