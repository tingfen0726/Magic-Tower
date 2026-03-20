#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP

#include "Character.hpp"
#include "Util/Input.hpp"
#include <vector>
#include "Map.hpp"
#include <string>

struct PlayerStats {
    int level = 1;  // 等級
    int hp = 1000;  // 生命
    int atk = 10;   // 攻擊
    int def = 10;   // 防禦
    int gold = 0;   // 金幣
    int exp = 0;    // 經驗值
};

struct Inventory {
    int yellowKey = 10;
    int blueKey = 1;
    int redKey = 1;
    bool hasholyCross = false;  // 神聖十字架
    bool haslightEmblem = false;// 聖光徽
    bool haswindCompass = false;// 風之羅盤
};

class Player : public Character {
public:
    Player();

    void Update(const std::shared_ptr<Map>& map) override;
    void SetPosition(int x, int y);
    int GetFloorChangeRequest() const { return m_FloorChangeRequest; }
    void ClearFloorChangeRequest() { m_FloorChangeRequest = 0; }
private:
    void HandleMovement(const std::shared_ptr<Map>& map);
    void UpdateAnimation();
    void SetImageFrame(int index);

    int m_CurrentFrame = 0; // 圖片動畫
    unsigned int m_LastFrameTime = 0; // 上次更新時間
    bool m_IsMoving = false; // 是否正在移動
    int m_CurrentGridX = 0; //陣列座標x
    int m_CurrentGridY = 0; //陣列座標y
    int m_MoveCooldown = 0; //移動冷卻
    int m_Direction = 0; //1正面 2背面 3左 4右
    int m_FloorChangeRequest = 0;
    PlayerStats m_Stats;
    Inventory m_Inventory;



};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PLAYER_HPP