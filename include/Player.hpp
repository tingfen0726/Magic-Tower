#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP

#include "Character.hpp"
#include "Block/Enemy.hpp"
#include "Util/Input.hpp"

struct PlayerStats {
    int level = 1;  // 等級
    int hp = 1000;  // 生命
    int atk = 10;   // 攻擊
    int def = 10;   // 防禦
    int gold = 0;   // 金幣
    int exp = 0;    // 經驗值
    int CalculateDamage(EnemyStats enemyStats) const;
};

struct Inventory {
    int yellowKey = 0;
    int blueKey = 0;
    int redKey = 0;
    bool hasholyCross = false;      // 神聖十字架
    bool hasredveri = false;        //炎之靈杖
    bool hasblueveri = false;       //冰之靈杖
    bool hasgreenveri = false;      //心之靈杖
    bool hasgemhoe = false;
    bool hasgodknifesign = false;   // 聖光徽
    bool haswindCompass = false;    // 風之羅盤
};

class Player : public Character {
public:
    Player();

    void Update() override;
    void SetPosition(int x, int y);
    PlayerStats& GetPlayerStats() {return m_Stats;}
    Inventory& GetInventory() {return m_Inventory;}
    int GetCurrentGridX() const { return m_CurrentGridX; }
    int GetCurrentGridY() const { return m_CurrentGridY; }
    void GetNextGrid(int& outX, int& outY, int& outDir);
    void MoveToGrid(int nextX, int nextY, int dir);
    void StepInPlace(int dir);
    bool Engage(EnemyStats enemyStats);
    void StopMove() {m_IsMoving = false; m_CurrentFrame = 0;};
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
    Inventory m_Inventory;



};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP