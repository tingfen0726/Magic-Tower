#include "UIText/FloorChangePanel.hpp"
#include <string>

FloorChangePanel::FloorChangePanel() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/Black.bmp"));
    m_Transform.translation = {142.0f, 0};
    m_Transform.scale = {0.5, 0.5};
    SetZIndex(88);
    SetVisible(false);
    m_Visible = false;

    m_Title = std::make_shared<UIText>(36, "樓層跳躍", Util::Color{255,255,255,255}, 150, 150);
    m_Title->SetZIndex(89);
    m_Title->SetVisible(false);
    AddChild(m_Title);

    for (int i = 0; i < 24; i++) {
        std::string floorText = (i == 23)? "地 下 層" : "第 " + std::to_string(i + 1) + " 層";
        auto floor = std::make_shared<UIText>(20, floorText, Util::Color{255,255,255,255}, 0, 0);
        floor->SetZIndex(89);
        floor->SetPosition(startX + (i / 7 * intervalX), startY - (i % 7) * intervalY);
        floor->SetVisible(false);
        AddChild(floor);
        m_Floors.push_back(floor);
    }

    m_SpaceText = std::make_shared<UIText>(16, "~~space~~", Util::Color{255,255,255,255}, 300, -190);
    m_SpaceText->SetZIndex(89);
    m_SpaceText->SetVisible(false);
    AddChild(m_SpaceText);

    m_Floors[m_ptr]->SetColor(Util::Color{255, 215, 0, 255});
    m_arrow = std::make_shared<Util::GameObject>();
    m_arrow->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/Special/right_arrow_gray.png"));
    m_arrow->m_Transform.translation = {-40, 90};
    m_arrow->m_Transform.scale = {0.65, 0.65};
    m_arrow->SetZIndex(89);
    m_arrow->SetVisible(false);
    AddChild(m_arrow);
}

void FloorChangePanel::ShowFloorChangePanel(bool Bool, bool Cheating_Mode) {
    if (!Bool) return;
    this->Cheating_Mode = Cheating_Mode;
    int numFloors = this->Cheating_Mode ? 24 : 20;
    int rowsPerCol = this->Cheating_Mode ? 6 : 7;
    float currentIntervalX = this->Cheating_Mode ? (intervalX * 0.8f) : intervalX;
    float currentStartX = this->Cheating_Mode ? (startX - 30.0f) : startX;

    for (int i = 0; i < m_Floors.size(); i++) {
        if (i < numFloors) {
            m_Floors[i]->SetPosition(currentStartX + (i / rowsPerCol * currentIntervalX), startY - (i % rowsPerCol) * intervalY);
            m_Floors[i]->SetVisible(true);
        } else {
            m_Floors[i]->SetVisible(false);
        }
    }

    ResetShopPanel();
    SetVisible(true);
    m_Visible = true;
    m_Title->SetVisible(true);
    m_SpaceText->SetVisible(true);
    m_arrow->SetVisible(!this->Cheating_Mode);
    m_MoveCooldown = 8;
}

int FloorChangePanel::ChangeOptions() {
    int maxIndex = this->Cheating_Mode ? 23 : 19;
    int rowsPerCol = this->Cheating_Mode ? 6 : 7;
    float currentIntervalX = this->Cheating_Mode ? (intervalX * 0.8f) : intervalX;

    if (!m_Visible) return -1;
    if (m_MoveCooldown > 0) {
        m_MoveCooldown--;
        return -1;
    }

    bool isMoved = false;
    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        if (m_ptr <= 0) { m_ptr = maxIndex;}
        else { m_ptr--;}
        isMoved = true;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        if (m_ptr >= maxIndex) { m_ptr = 0;}
        else { m_ptr++;}
        isMoved = true;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        CloseFloorChangePanel();
        return m_ptr + 1;
    }

    if (isMoved) {
        m_arrow->m_Transform.translation = {-40.0f + (m_ptr / rowsPerCol * currentIntervalX), 90.0f - (m_ptr % rowsPerCol) * intervalY};

        m_Floors[m_ptr]->SetColor(Util::Color{255, 215, 0, 255});
        for (int i = 0; i < m_Floors.size(); i++) {
            if (i != m_ptr) m_Floors[i]->SetColor(Util::Color{255, 255, 255, 255});
        }
        m_MoveCooldown = 8;
    }
    return -1;
}

void FloorChangePanel::CloseFloorChangePanel() {
    SetVisible(false);
    m_Visible = false;
    m_Title->SetVisible(false);
    for (auto floor : m_Floors) {
        floor->SetVisible(false);
    }
    m_SpaceText->SetVisible(false);
    m_arrow->SetVisible(false);
}

void FloorChangePanel::ResetShopPanel() {
    m_ptr = 0;
    m_arrow->m_Transform.translation = {-40.0f, 90};
    for (int i = 0; i < m_Floors.size(); i++) {
        m_Floors[i]->SetColor(Util::Color{255, 255, 255, 255});
    }
    m_Floors[0]->SetColor(Util::Color{255, 215, 0, 255});
}

void FloorChangePanel::Update() {
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
