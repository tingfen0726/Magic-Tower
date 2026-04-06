#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_NPCDIALOG_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_NPCDIALOG_HPP

#include "UIText.hpp"
#include "Util/GameObject.hpp"
#include "Block/SpecificNPCs.hpp"
#include "Player.hpp"

class NPCDialog : public Util::GameObject {
public:
    NPCDialog();
    void StareDialog(std::vector<DialogueLine> Dialogues);
    bool GetIsDialogue() {return m_IsDialogue;};
    void NextDialogue();
    void Update();
private:
    void CloseDialog();
    void UpdateDialogue();

    std::shared_ptr<Util::GameObject> m_SpeakerIcon;
    std::shared_ptr<UIText> m_SpeakerName;
    std::shared_ptr<UIText> m_SpeakerDialog;
    std::shared_ptr<UIText> m_SpaceText;
    std::vector<DialogueLine> m_dialogues;
    int m_MoveCooldown = 0;
    int m_progress;
    bool m_IsDialogue;

    unsigned int m_LastBlinkTime = 0;
    bool m_IsHighOpacity = true;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_NPCDIALOG_HPP