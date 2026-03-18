#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_MAP_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_MAP_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <vector>
#include <string>

const float m_Step = 56.7f;
const float m_StartX = -141.5f;
const float m_StartY = 283.6f;

class Block : public Util::GameObject {
public:
    Block(const std::vector<std::string>& imagePath, int x, int y, int id) {
        SetDrawable(std::make_shared<Util::Image>(imagePath[0]));
        m_Transform.translation = {m_StartX + (x * m_Step), m_StartY - (y * m_Step)};
        m_Transform.scale = {0.74f, 0.74f};
        m_imagePath = imagePath;
        posX = x;
        posY = y;
        m_ID = id;
    }
    virtual ~Block() = default;
    void SetImageFrame(int index);
    virtual void UpdateAnimation() {}
    std::vector<int> GetPosition() { return {posX, posY}; }
    int GetID() { return m_ID; }
protected:
    int m_ID;
    std::vector<std::string> m_imagePath;
    unsigned int m_LastFrameTime = 0;
    int m_CurrentFrame = 0;
    int posX, posY;
};

class Map {
public:
    Map();
    // 讀取二維陣列，並把對應的牆壁實體化
    void LoadLevel(const std::vector<std::vector<int>>& levelData);

    void SetVisible(bool visible);
    void Update();

    std::vector<std::shared_ptr<Block>> GetBlocks() const { return m_Blocks; }

    const std::vector<std::vector<int>>& GetLevelData() const { return m_LevelData; }

private:
    std::vector<std::vector<int>> m_LevelData;
    std::vector<std::shared_ptr<Block>> m_Blocks; // 裝著畫面上所有牆壁的陣列

};
#endif //REPLACE_WITH_YOUR_PROJECT_NAME_MAP_HPP