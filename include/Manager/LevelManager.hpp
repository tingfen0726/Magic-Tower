#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP

#include <memory>
#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "Util/Renderer.hpp"
#include "FloorData.hpp"
#include "UIText.hpp"

class LevelManager {
public:
    LevelManager(std::shared_ptr<Map> map,
                 std::shared_ptr<Player> player,
                 Util::Renderer& renderer);

    void InitFloorData();
    bool JumpToFloor(int targetFloor, bool checkVisited = false);
    void ProcessStair(int stairX, int stairY);
    void ChangeRemoteBlock(int targetFloor, int x, int y, int newID);
    void EnemyReinforcements(int stage);
    void MoveNPC(std::shared_ptr<NPC> npcPtr, int nextX, int nextY) { m_Map->MoveNPC(npcPtr, nextX, nextY); }

    int GetCurrentFloor() const { return m_CurrentFloor; }
    std::vector<FloorData>& GetFloorData() { return m_FloorData; }

private:
    std::shared_ptr<Map> m_Map;
    std::shared_ptr<Player> m_Player;
    Util::Renderer* m_Renderer;

    int m_CurrentFloor = 0;
    std::vector<FloorData> m_FloorData;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP