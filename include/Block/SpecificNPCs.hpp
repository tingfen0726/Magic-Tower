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
                    }, false},
                    {{
                        {Speaker::FAIRY, "　嗯?!你手裡的那個東西是\n甚麼?"},
                        {Speaker::PLAYER, "　這個? 這是一個老人交給\n我的，是他叫我帶他來找你"},
                        {Speaker::PLAYER, "的。他說你知道他的來歷和\n作用。"},
                        {Speaker::FAIRY, "　這個東西是仙界的聖物名\n叫 \"靈之杖\" ，是很久以前"},
                        {Speaker::FAIRY, "的一個聖者留下的。\n　它們一共有三個，分別鑲"},
                        {Speaker::FAIRY, "著紅、綠、藍三種顏色的寶\n石。"},
                        {Speaker::FAIRY, "　你現在拿著的是一顆鑲有\n藍寶石的 \"冰之靈杖\" 應該"},
                        {Speaker::FAIRY, "還有一個鑲有綠寶石的\n \"心之靈杖\" 和鑲有紅寶石"},
                        {Speaker::FAIRY, "的 \"炎之靈杖\" 。"},
                        {Speaker::FAIRY, "　在這座塔的下面，封印著\n一支魔界的世獸，名叫"},
                        {Speaker::FAIRY, "\"血影\"，這三把 \"靈之杖\"\n就是封印的鑰匙。"},
                        {Speaker::PLAYER, "　封印鑰匙?"},
                        {Speaker::FAIRY, "　每一個 \"靈之杖\" 裡面都\n有著很強的魔法力量，如果"},
                        {Speaker::FAIRY, "被惡魔得到了將會使它的力\n量倍增。"},
                        {Speaker::FAIRY, "　如果被惡魔將他們三個找\n齊的話。"},
                        {Speaker::FAIRY, "　那麼 \"血影\" 的封印便會\n解除!"},
                        {Speaker::FAIRY, "　勇士，你還是快去把我要\n的東西找來把，等我恢復了"},
                        {Speaker::FAIRY, "魔力，我就可以幫你將 \"靈\n之杖\" 中的魔力都開放出來!"}
                    }, false},
                    {{
                        {Speaker::FAIRY, "　勇敢的去吧！勇士！"}
                    }, false},
                    {{
                        {Speaker::PLAYER, "　仙子，我已經將那個十字\n架找到了。"},
                        {Speaker::FAIRY, "　你做得很好，\n　那麼，現在我就開始授予"},
                        {Speaker::FAIRY, "你更強的力量!\n　咪拉哆咪嘩......"},
                        {Speaker::FAIRY, "　好了，我已經將你現在的\n能力提升了!"},
                        {Speaker::FAIRY, "　記住：如果你沒有足夠的\n實力的話，不要去第二十一"},
                        {Speaker::FAIRY, "層! 在那一層裡，你所有寶\n物的法力都會失去作用!"},
                        {Speaker::FAIRY, "　快走吧，殺死魔王後，來\n第二十二層上找我!"}
                    }, false}
                };
                break;
            case Config::ID::FAIRY_22:
                DialogueStages = {
                {{
                    {Speaker::FAIRY, "　做得很好。現在你已經將\n那個可惡的冥靈魔王給殺了"},
                    {Speaker::FAIRY, "，快去找另外的兩個\"靈杖\"\n吧，找齊了以後再來找我!"},
                    {Speaker::FAIRY, "　要記住，如果我不把封印\n解開的話，最底層的怪物你"},
                    {Speaker::FAIRY, "是殺不了的!"}
                }, false},
                {{
                    {Speaker::FAIRY, "　快去找吧，勇士!"}
                }, false},
                {{
                    {Speaker::PLAYER, "　快看，我全部都找到了，\n我找齊所有了!"},
                    {Speaker::FAIRY, "　嗯，不錯，現在我們可以\n解除這裏面的封印了!"},
                    {Speaker::FAIRY, "　那就讓我們開始吧!\n　神之 \"靈杖\" 呀，放射出"},
                    {Speaker::FAIRY, "你們的魔力吧!\n　哈哩咪哆唏咪啦~~~~~~"},
                    {Speaker::PLAYER, "　......\n　(又來了! )"},
                    {Speaker::FAIRY, "　......\n　好了，我已經將它們三個"},
                    {Speaker::FAIRY, " \"靈之杖\" 的魔力都開放出\n來了! "},
                    {Speaker::FAIRY, "　公主就由我來救出去，你\n快去最底層殺了那個大魔頭"},
                    {Speaker::FAIRY, "吧! 要記住，如果沒有萬分\n的把握，一定不要去開最後"},
                    {Speaker::FAIRY, "那扇花形門! 一旦進去了，\n你將不能再回來! "}
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
        if ((Dialogues[4].isCompleted && m_ID == Config::ID::FAIRY_0)
            || (Dialogues[2].isCompleted && m_ID == Config::ID::FAIRY_22)) {
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

class ThiefNPC : public NPC {
public:
    ThiefNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::THIEF_4:
                DialogueStages = {
                    {{
                        {Speaker::PLAYER, "　你已經得救了!"},
                        {Speaker::THIEF, "　啊，那真是太好了，我又\n可以在這裡面尋寶了!"},
                        {Speaker::THIEF, "　噢，還沒有自我介紹，我\n叫捷克，是這附近有名的小"},
                        {Speaker::THIEF, "偷，什麼金銀財寶我樣樣都\n偷過。"},
                        {Speaker::THIEF, "　不過這次運氣可不是太好\n剛進來就被抓了。"},
                        {Speaker::THIEF, "　現在你幫我打開了門，那\n我就幫你做一件事吧。"},
                        {Speaker::PLAYER, "　快走吧，外面還有很多怪\n物，我可能顧不上你。"},
                        {Speaker::THIEF, "　不，不，不會有事的。\n　快說吧，叫我做什麼?"},
                        {Speaker::PLAYER, "　......\n你會開門嗎?"},
                        {Speaker::THIEF, "　那當然。"},
                        {Speaker::PLAYER, "　那就請你幫我打開第二層\n的門吧!"},
                        {Speaker::THIEF, "　那個簡單，不過，如果你\n能幫我找到一把嵌了紅寶石"},
                        {Speaker::THIEF, "的鐵榔頭的話，我還能幫你\n打通第十八層的路。"},
                        {Speaker::PLAYER, "　嵌了紅寶石的鐵榔頭?\n　好吧，我幫你找找。"},
                        {Speaker::THIEF, "　非常地感謝。一會兒我便\n會將第二層的門打開。"},
                        {Speaker::THIEF, "　如果你找到那個鐵榔頭的\n話，還是來這裡找我!"}
                    }, false},
                    {{
                        {Speaker::THIEF, "　如果你找到那個鐵榔頭的\n話，還是來這裡找我!"}
                    }, false},
                    {{
                        {Speaker::PLAYER, "　哈，快看我找到了甚麼!"},
                        {Speaker::THIEF, "　太好了，這個東西果然是\n在這裡。"},
                        {Speaker::THIEF, "　好吧，我這就去幫你修好\n第十八層的路面。"}
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
        if (Dialogues[2].isCompleted) {
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

class DonorNPC : public NPC {
public:
    DonorNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::ELDER_2:
                DialogueStages = {
                {{
                    {Speaker::PLAYER, "　您已經得救了!"},
                    {Speaker::ELDER, "　噢，我的孩子，真是太感\n謝你了!"},
                    {Speaker::ELDER, "　這個地方真是又髒又壞，\n我真的是快待不下去了。"},
                    {Speaker::PLAYER, "　快走吧，我還得救走被關\n在這裡的公主。"},
                    {Speaker::ELDER, "　噢，你是來救公主的，為\n了表示對你的感謝，這個東"},
                    {Speaker::ELDER, "西就送給你吧，這還是我年\n輕的時候用過的。"},
                    {Speaker::ELDER, "　拿著它去解救公主吧!"}
                 }, false}
                };
                break;
            case Config::ID::SHOPKEEPER_2:
                DialogueStages = {
                {{
                    {Speaker::PLAYER, "　您已經得救了!"},
                    {Speaker::SHOPKEEPER, "　噢，是嘛! 真是太感謝你\n了!"},
                    {Speaker::SHOPKEEPER, "　我是個商人，不知為甚麼\n被抓這裡來了。"},
                    {Speaker::PLAYER, "　快走吧，現在你已經自由\n了。"},
                    {Speaker::SHOPKEEPER, "　噢，對對對，我已經自由\n了。"},
                    {Speaker::SHOPKEEPER, "　那這個東西就給你吧，本\n來我是準備賣錢的。"},
                    {Speaker::SHOPKEEPER, "　相信它對你一定很有幫助！"}
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

class TraderNPC : public NPC {
public:
    TraderNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::SHOPKEEPER_15:
                DialogueStages = {
                {{
                    {Speaker::SHOPKEEPER, "　啊哈，歡迎你的到來!\n　我這裡有一件對你來說非"},
                    {Speaker::SHOPKEEPER, "常好的寶物，只要你出得起\n錢，我就賣給你。"},
                    {Speaker::PLAYER, "　什麼寶物? 要多少錢?"},
                    {Speaker::SHOPKEEPER, "　是這個遊戲最好的盾牌，\n防禦值可以增加 120點，而"},
                    {Speaker::SHOPKEEPER, "你只要出 500個金幣就可以\n買下。"},
                    {Speaker::SHOPKEEPER, "　怎麼樣? 你有500個金幣嗎?"}
                }, false},
                {{
                    {Speaker::PLAYER, "　我沒有500個金幣。"},
                    {Speaker::SHOPKEEPER, "　那等你有的時候再來找我\n吧!"}
                 }, false},
                {{
                    {Speaker::PLAYER, "　我有500個金幣。"},
                    {Speaker::SHOPKEEPER, "　好，成交!"},
                 }, false}
                };
                break;
            case Config::ID::ELDER_15:
                DialogueStages = {
                {{
                    {Speaker::ELDER, "　你好，勇敢的孩子，你終\n於來到這裡了。"},
                    {Speaker::ELDER, "　我將給你一個非常好的寶\n物，它可以使你的攻擊力提"},
                    {Speaker::ELDER, "升120點，但這必須得用你\n500點經驗來進行交換，考"},
                    {Speaker::ELDER, "慮一下子吧!"}
                }, false},
                {{
                    {Speaker::PLAYER, "　我再考慮考慮吧..."},
                    {Speaker::ELDER, "　等你考慮好了再來找我吧!"}
                }, false},
               {{
                   {Speaker::PLAYER, "　好吧，那就將那把劍給我\n吧!"},
                   {Speaker::ELDER, "　那好，這把劍就給你了!"}
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
        if (Dialogues[2].isCompleted) {
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
class ElderNPC : public NPC {
public:
    ElderNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::ELDER_16:
                DialogueStages = {
                {{
                    {Speaker::ELDER, "　年輕人，你終於來了!"},
                    {Speaker::PLAYER, "　您怎麼了?"},
                    {Speaker::ELDER, "　我已經快封印不住它了，\n請你將這個東西交給彩蝶"},
                    {Speaker::ELDER, "仙子，她會告訴你這是什麼\n東西，有什麼用的!"},
                    {Speaker::ELDER, "　快去吧，再遲就來不及了!"}
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

class princessNPC : public NPC {
public:
    princessNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::PRINCESS:
                DialogueStages = {
                {{
                    {Speaker::PLAYER, "　公主! 你得救了!"},
                    {Speaker::PRINCESS, "　啊，你是來救我的嗎?"},
                    {Speaker::PLAYER, "　是的，我是奉國王的命令\n來救你的。"},
                    {Speaker::PLAYER, "　請你快隨我出去吧!"},
                    {Speaker::PRINCESS, "　不，我還不想走。"},
                    {Speaker::PLAYER, "　為什麼? 這裡面到處都是\n惡魔。"},
                    {Speaker::PRINCESS, "　正是因為這裡面到處都是\n惡魔，所以才不可以就這樣"},
                    {Speaker::PRINCESS, "出去，我要看著那個惡魔被\n殺死!"},
                    {Speaker::PRINCESS, "　英勇的勇士，如果你能夠\n將那個大魔王殺死，我就和"},
                    {Speaker::PRINCESS, "你一起出去!"},
                    {Speaker::PLAYER, "　大惡魔? 我已經殺死了一\n個魔王!"},
                    {Speaker::PRINCESS, "　大惡魔在這座塔的最頂層\n，你殺死的可能是一個小隊"},
                    {Speaker::PRINCESS, "長之類的惡魔。"},
                    {Speaker::PLAYER, "　好，那你等著，等我殺了\n那個惡魔再來這裡找你!"},
                    {Speaker::PRINCESS, "　大惡魔比你剛才殺死的那\n個厲害多了。"},
                    {Speaker::PRINCESS, "　而且它還會變身，變身後\n的魔王它的攻擊力和防禦力"},
                    {Speaker::PRINCESS, "都會提升至少一半以上，你\n得小心!"},
                    {Speaker::PRINCESS, "　請一定要殺死大魔王! "}
                }, false},
                {{
                    {Speaker::PRINCESS, "　加油!!"}
                }, false}
                };
                break;
        }
        SetDialogues(DialogueStages);
        SetIsPersistent(true);
    }
};
class vampireNPC : public NPC {
public:
    vampireNPC(const std::vector<std::string> &imagePath, int x, int y, int id) : NPC(imagePath, x, y, id) {
        std::vector<DialogueStage> DialogueStages = {};
        switch (id) {
            case Config::ID::VAMPIRE_19:
                DialogueStages = {
                {{
                    {Speaker::PLAYER, "　大魔頭，你的死期\n到了!"},
                    {Speaker::VAMPIRE, "哈哈哈......\n你也真是有意思，別以為"},
                    {Speaker::VAMPIRE, "蝶仙那傢伙給了你力量你就\n可以打敗我，想打敗我"},
                    {Speaker::VAMPIRE, "你還早著呢!"},
                    {Speaker::PLAYER, "　廢話少說，去死吧!"}
                }, false}
                };
                break;
        }
        SetDialogues(DialogueStages);
        SetIsPersistent(false);
    }
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
                    {Speaker::SYSTEM, "　如果你需要更多力量再來\n這裡找我!"},
                 }, false},
                {{
                    {Speaker::PLAYER, "　我需要更多力量!"},
                    {Speaker::SYSTEM, "　我將賜予你我所有的神秘\n力量!!"},
                    {Speaker::SYSTEM, "　祝你好運"},
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