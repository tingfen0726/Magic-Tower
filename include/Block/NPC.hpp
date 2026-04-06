#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_NPC_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_NPC_HPP

#include "Map.hpp"
enum class Speaker {
    PLAYER,
    FAIRY,
    PRINCESS,
    ELDER,
    SHOPKEEPER,
    THIEF,
    SYSTEM
};
struct DialogueLine {
    Speaker speaker;
    std::string text;
};
struct DialogueStage {
    std::vector<DialogueLine> dialogues;
    bool isCompleted = false;
};

class NPC : public Block {
public:
    NPC(const std::vector<std::string>& imagePath, int x, int y, int id);
    virtual void UpdateAnimation();

    void SetDialogues(std::vector<DialogueStage> DialogueStages) {m_DialogueStages = DialogueStages;};
    std::vector<DialogueStage> GetDialogues(){return m_DialogueStages;};
    void SetIsPersistent(bool Bool) {m_isPersistent = Bool;};
    bool GetIsPersistent() {return m_isPersistent;};
    int GetCurrentStage() {return m_currentStage;};
    void AddCurrentStage();
    void SetCurrentStage(int currentStage) { m_currentStage = currentStage; };
    void IsCompleted() {m_DialogueStages[m_currentStage].isCompleted = true;};
    // void IsAllComplete() {m_AllComplete = true;};
    // bool GetIsAllComplete() {return m_AllComplete;};

private:
    // bool m_AllComplete = false;
    int m_currentStage = 0;
    std::vector<DialogueStage> m_DialogueStages;
    bool m_isPersistent = false; //false會消失 true不會消失

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_NPC_HPP