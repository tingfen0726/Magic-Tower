#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SPECIFICNPCS_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SPECIFICNPCS_HPP
#include  "NPC.hpp"

class FairyNPC : public NPC {
public:
    FairyNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::FAIRY_0:
                DialogueStages = {
                    {{
                       {Speaker::PLAYER, "　......"},
                       {Speaker::FAIRY, "　你醒了!"},
                       {Speaker::PLAYER, "　你是誰? 我在哪裡?"},
                       {Speaker::FAIRY, "　我是這裡的仙子，剛才你\n被這裡的小怪打昏了。"},
                       {Speaker::PLAYER, "　劍，劍，我的劍呢?"},
                       {Speaker::FAIRY, "　你的劍被他們搶走了，我\n只來得及將你救出來。"},
                       {Speaker::PLAYER, "　那，公主呢?　我是來救\n公主的。"},
                       {Speaker::FAIRY, "　公主還在裡面，你這樣進\n去是打不過裡面小怪的。"},
                       {Speaker::PLAYER, "　那我怎麼辦，我答應了\n國王一定要把公主救出來"},
                       {Speaker::PLAYER, "的，那我現在應該怎麼辦\n呢?"},
                       {Speaker::FAIRY, "　放心把，我把我的力量借\n給你，你就可以打贏那些小"},
                       {Speaker::FAIRY, "怪了，不過，你得先幫我去\n找一樣東西，找到了再來這"},
                       {Speaker::FAIRY, "裡找我。"},
                       {Speaker::PLAYER, "找東西? 找什麼東西?"},
                       {Speaker::FAIRY, "是一個十字架，中間有一顆\n紅色的寶石。"},
                       {Speaker::PLAYER, "那東西有甚麼用嗎?"},
                       {Speaker::FAIRY, "　我本是這座塔守護者，可\n不久前，從北方來了一批惡"},
                       {Speaker::FAIRY, "魔，他們佔領了這座塔，並\n將我的魔力封在了這個十字"},
                       {Speaker::FAIRY, "架裡面，如果你能將她帶出\n塔來，那我的魔力邊會慢慢"},
                       {Speaker::FAIRY, "地恢復，到那時我便可以把\n力量借給你去救出公主了。"},
                       {Speaker::FAIRY, "要記住，只有用我的魔力才\n可以打開二十一層的門。"},
                       {Speaker::PLAYER, "　好吧，我試試看。"},
                       {Speaker::FAIRY, "　剛才我去看過了，你的劍\n被放在三樓，你的盾在五樓"},
                       {Speaker::FAIRY, "上，而那個十字架被放在七\n樓，要到七樓，你得先取回"},
                       {Speaker::FAIRY, "你的劍和盾。\n　另外，在塔裡的其他樓層"},
                       {Speaker::FAIRY, "上，還有一些存放了好幾百\n年的寶劍和寶物，如果得到"},
                       {Speaker::FAIRY, "它們，對於你對付這裡面的\n怪物將有很大的幫助。"},
                       {Speaker::PLAYER, "　可是，我怎麼進去呢?"},
                       {Speaker::FAIRY, "　我這裡有三把鑰匙，你先\n拿去，在塔裡面還有很多這"},
                       {Speaker::FAIRY, "樣的鑰匙，你一定要珍惜使\n用。"},
                       {Speaker::FAIRY, "勇敢的去吧! 勇士!"}
                    }, false},
                    {{
                        {Speaker::FAIRY, "　勇敢的去吧！勇士！"}
                    }, false}
                };
                break;
        }
        SetDialogues(DialogueStages);
        SetIsPersistent(true);
    }
    void UpdateAnimation() override{
        unsigned int currentTime = SDL_GetTicks();
        // if (GetResolved()) {
        //     m_CurrentFrame = m_imagePath.size() - 1;
        //     SetImageFrame(m_CurrentFrame);
        //     return;
        // }
        if (currentTime - m_LastFrameTime > 150) {
            m_CurrentFrame = (m_CurrentFrame + 1) % (m_imagePath.size() - 1);
            SetImageFrame(m_CurrentFrame);
            m_LastFrameTime = currentTime;
        }
    };
};

class ThiefNPC : public NPC {
public:
    ThiefNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::THIEF_4:
                DialogueStages = {
                    {{
                       {Speaker::THIEF, "　你好我是小偷，我幫你開\n第二層門，並找到紅寶石榔"},
                        {Speaker::THIEF, "頭給我"},
                       {Speaker::PLAYER, "　好吧，我去找"},
                       {Speaker::THIEF, "　加油!"},
                    }, false},
                    {{
                        {Speaker::THIEF, "　加油!"}
                    }, false},
                    {{
                        {Speaker::PLAYER, "　給你!我找到了"},
                        {Speaker::THIEF, "　唉呀!你找到了!"}
                    }, false},
                    {{
                        {Speaker::THIEF, "　......"}
                    }, false}
                };
                break;
        }
        SetDialogues(DialogueStages);
        SetIsPersistent(true);
    }
    void UpdateAnimation() override{
        unsigned int currentTime = SDL_GetTicks();
        // if (GetResolved()) {
        //     m_CurrentFrame = m_imagePath.size() - 1;
        //     SetImageFrame(m_CurrentFrame);
        //     return;
        // }
        if (currentTime - m_LastFrameTime > 150) {
            m_CurrentFrame = (m_CurrentFrame + 1) % (m_imagePath.size() - 1);
            SetImageFrame(m_CurrentFrame);
            m_LastFrameTime = currentTime;
        }
    };
};

class DonorNPC : public NPC {
public:
    DonorNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::ELDER_2:
                DialogueStages = {
                {{
                    {Speaker::ELDER, "　你好我是神秘老人贈與你\n鋼劍"},
                    {Speaker::PLAYER, "　謝謝"}
                 }, false}
                };
                break;
            case Config::ID::SHOPKEEPER_2:
                DialogueStages = {
                {{
                    {Speaker::SHOPKEEPER, "　你好我是商人贈與你鋼盾"},
                    {Speaker::PLAYER, "　謝謝"}
                 }, false}
                };
                break;
        }
        SetDialogues(DialogueStages);
        SetIsPersistent(false);
    }
    void UpdateAnimation() override{
        unsigned int currentTime = SDL_GetTicks();
        auto Dialogues = GetDialogues();
        if (Dialogues[0].isCompleted) {
            m_CurrentFrame = m_imagePath.size() - 1;
            SetImageFrame(m_CurrentFrame);
            return;
        }
        if (currentTime - m_LastFrameTime > 150) {
            m_CurrentFrame = (m_CurrentFrame + 1) % (m_imagePath.size() - 1);
            SetImageFrame(m_CurrentFrame);
            m_LastFrameTime = currentTime;
        }
    };
};

class systemNPC : public NPC {
public:
    systemNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::SYSTEM_NPC:
                DialogueStages = {
                {{
                    {Speaker::SYSTEM, "　......"},
                    {Speaker::SYSTEM, "　放棄了嗎?\n　還是再考慮一下?"},
                 }, false},
                {{
                    {Speaker::PLAYER, "我決定好了!"},
                    {Speaker::SYSTEM, "　好的。\n　那我將賜予你神秘力量。"},
                    {Speaker::SYSTEM, "祝你好運"},
                 }, false},
                {{
                    {Speaker::SYSTEM, "　祝你好運"},
                 }, false}
                };

                break;
        }
        SetDialogues(DialogueStages);
        SetIsPersistent(true);
    }
};



#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SPECIFICNPCS_HPP