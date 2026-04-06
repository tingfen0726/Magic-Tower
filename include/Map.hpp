#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_MAP_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_MAP_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "GameConstants.hpp"
#include "PlayerConstants.hpp"
#include <vector>
#include <string>
class NPC;

class Block : public Util::GameObject {
public:
    Block(const std::vector<std::string>& imagePath, int x, int y, int id) {
        SetDrawable(std::make_shared<Util::Image>(imagePath[0]));
        m_Transform.translation = {Config::MAP_OFFSET_X + (x * Config::TILE_SIZE), Config::MAP_OFFSET_Y - (y * Config::TILE_SIZE)};
        m_Transform.scale = {0.74f, 0.74f};
        m_imagePath = imagePath;
        posX = x;
        posY = y;
        m_ID = id;
        SetZIndex(20);
    }
    virtual ~Block() = default;
    void SetImageFrame(int index);
    virtual void UpdateAnimation() {}
    std::vector<int> GetPosition() { return {posX, posY}; }
    void SetPosition(int x, int y) {
        posX = x; posY = y;
        m_Transform.translation = {
            Config::MAP_OFFSET_X + (posX * Config::TILE_SIZE),
            Config::MAP_OFFSET_Y - (posY * Config::TILE_SIZE)
        };
    }
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
    void LoadLevel(const std::vector<std::vector<int>>& levelData);
    void RestoreNPCs(const std::vector<std::shared_ptr<NPC>>& savedNPCs);

    void SetVisible(bool visible);
    void Update();

    std::vector<std::shared_ptr<Block>> GetBlocks() const { return m_Blocks; }
    void AddBlock(std::shared_ptr<Block> block){m_Blocks.push_back(block);};
    const std::vector<std::vector<int>>& GetLevelData() const { return m_LevelData; }
    void RemoveBlock(int x, int y);
    void MoveNPC(std::shared_ptr<NPC> npcPtr, int nextX, int nextY);

private:
    std::vector<std::vector<int>> m_LevelData;
    std::vector<std::shared_ptr<Block>> m_Blocks;

};
#endif //REPLACE_WITH_YOUR_PROJECT_NAME_MAP_HPP