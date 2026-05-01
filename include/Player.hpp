#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP

#include "Character.hpp"
#include "Block/Enemy.hpp"
#include "PlayerConstants.hpp"
#include "Util/Input.hpp"

struct  PlayerStats {
    int level = 1;  // 等級
    int hp = 1000;  // 生命
    int atk = 10;   // 攻擊
    int def = 10;   // 防禦
    int gold = 0;   // 金幣
    int exp = 0;    // 經驗值
    int CalculateDamage(EnemyStats enemyStats) const;
};

struct PlayerInventory {
    int yellowKey = 0;
    int blueKey = 0;
    int redKey = 0;
    bool hasholyCross = false;      // 神聖十字架
    bool hasredveri = false;        //炎之靈杖
    bool hasblueveri = false;       //冰之靈杖
    bool hasgreenveri = false;      //心之靈杖
    bool hasgemhoe = false;         //紅寶石榔頭
    bool hasgodknifesign = true;   // 聖光徽
    bool haswindCompass = false;    // 風之羅盤
};

class Player : public Character {
public:
    Player();

    void Update() override;
    void SetPosition(int x, int y);//設置位置
    PlayerStats GetPlayerStats() {return m_Stats;}//回傳stats
    PlayerInventory GetInventory() {return m_Inventory;}//回傳inv
    int GetCurrentGridX() const { return m_CurrentGridX; }//回傳x
    int GetCurrentGridY() const { return m_CurrentGridY; }//回傳y
    void GetNextGrid(int& outX, int& outY, int& outDir);//回傳下一步
    void MoveToGrid(int nextX, int nextY, int dir);//移動
    void StepInPlace(int dir);//原地踏步
    // bool Engage(EnemyStats enemyStats);//攻擊
    void StopMove() {m_IsMoving = false; m_CurrentFrame = 0;};//停止移動

    void SetStats(PlayerLabel::Stat type, int value);
    void SetKey(PlayerLabel::Key type, int value);
    void SetItem(PlayerLabel::Item type, bool value);

    void AddStats(PlayerLabel::Stat type, int value);
    void AddKey(PlayerLabel::Key type, int value);

private:
    void UpdateAnimation();
    void SetImageFrame(int index);

    int m_CurrentFrame = 0; // 圖片動畫
    unsigned int m_LastFrameTime = 0; // 上次更新時間
    bool m_IsMoving = false; // 是否正在移動
    int m_CurrentGridX = 0; //陣列座標x
    int m_CurrentGridY = 0; //陣列座標y
    int m_MoveCooldown = 0; //移動冷卻
    int m_Direction = 0; //1正面 2背面 3左 4右
    PlayerStats m_Stats;
    PlayerInventory m_Inventory;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP