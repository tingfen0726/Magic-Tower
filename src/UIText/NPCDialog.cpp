#include "UIText/NPCDialog.hpp"


NPCDialog::NPCDialog() {
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/NPCDialog.bmp"));
    m_Transform.translation = {142.0f, 0};
    m_Transform.scale = {0.5, 0.5};
    SetZIndex(88);
    SetVisible(false);

    m_SpeakerIcon = std::make_shared<Util::GameObject>();
    m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/player.bmp"));
    m_SpeakerIcon->m_Transform.translation = {27.0f, 38.0f};
    m_SpeakerIcon->m_Transform.scale = {0.475, 0.475};
    m_SpeakerIcon->SetZIndex(89);
    m_SpeakerIcon->SetVisible(false);
    AddChild(m_SpeakerIcon);

    m_SpeakerName = std::make_shared<UIText>(20, "勇者", Util::Color{255,255,255,255}, 87, 38);
    m_SpeakerName->SetZIndex(89);
    m_SpeakerName->SetVisible(false);
    AddChild(m_SpeakerName);

    m_SpeakerDialog = std::make_shared<UIText>(20, "　你好我是勇者，我要來攻\n打這座塔，救出公主", Util::Color{255,255,255,255}, 149, -18);
    m_SpeakerDialog->SetZIndex(89);
    m_SpeakerDialog->SetVisible(false);
    AddChild(m_SpeakerDialog);

    m_SpaceText = std::make_shared<UIText>(16, "~~space~~", Util::Color{255,255,255,255}, 240, -60);
    m_SpaceText->SetZIndex(89);
    m_SpaceText->SetVisible(false);
    AddChild(m_SpaceText);
}

void NPCDialog::NextDialogue() {
    if (m_MoveCooldown > 0) {
        m_MoveCooldown--;
        return;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
        m_progress += 1;
        m_MoveCooldown = 8;
        if (m_progress >= static_cast<int>(m_dialogues.size())){
            CloseDialog();
            m_MoveCooldown = 0;
            m_IsDialogue = false;
            return;
        }
        UpdateDialogue();
    }
}

void NPCDialog::StartDialog(std::vector<DialogueLine> Dialogues) {
    SetVisible(true);
    m_SpeakerIcon->SetVisible(true);
    m_SpeakerName->SetVisible(true);
    m_SpeakerDialog->SetVisible(true);
    m_SpaceText->SetVisible(true);
    m_dialogues = Dialogues;
    m_IsDialogue = true;
    m_MoveCooldown = 8;
    m_progress = 0;
    UpdateDialogue();
}

// void NPCDialog::ShowNPCDialog(int speaker, std::vector<DialogueLine> Dialogues) {
//
// }

void NPCDialog::UpdateDialogue() {
    if (m_dialogues.empty() || m_progress >= m_dialogues.size()) {
        return;
    }
    switch (m_dialogues[m_progress].speaker) {
        case Speaker::PLAYER:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/player.bmp"));
            m_SpeakerName->UpdateText("勇者");
            m_SpeakerName->m_Transform.translation = {87, 38};
            break;
        case Speaker::FAIRY:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/fairy.bmp"));
            m_SpeakerName->UpdateText("仙子");
            m_SpeakerName->m_Transform.translation = {87, 38};
            break;
        case Speaker::PRINCESS:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/princess.bmp"));
            m_SpeakerName->UpdateText("公主");
            m_SpeakerName->m_Transform.translation = {87, 38};
            break;
        case Speaker::ELDER:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/elder.bmp"));
            m_SpeakerName->UpdateText("神秘老人");
            m_SpeakerName->m_Transform.translation = {107, 38};
            break;
        case Speaker::SHOPKEEPER:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/shopkeeper.bmp"));
            m_SpeakerName->UpdateText("商人");
            m_SpeakerName->m_Transform.translation = {87, 38};
            break;
        case Speaker::THIEF:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/thief.bmp"));
            m_SpeakerName->UpdateText("小偷");
            m_SpeakerName->m_Transform.translation = {87, 38};
            break;
        case Speaker::VAMPIRE:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/vampire_npc.bmp"));
            m_SpeakerName->UpdateText("冥靈魔王");
            m_SpeakerName->m_Transform.translation = {107, 38};
            break;
        case Speaker::SYSTEM:
            m_SpeakerIcon->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/Image/NPC/system.bmp"));
            m_SpeakerName->UpdateText("???");
            m_SpeakerName->m_Transform.translation = {87, 38};
            break;
    }
    m_SpeakerDialog->UpdateText(m_dialogues[m_progress].text);
}

void NPCDialog::CloseDialog() {
    SetVisible(false);
    m_SpeakerIcon->SetVisible(false);
    m_SpeakerName->SetVisible(false);
    m_SpeakerDialog->SetVisible(false);
    m_SpaceText->SetVisible(false);
}

void NPCDialog::Update() {
    if (!m_IsDialogue) return;

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
