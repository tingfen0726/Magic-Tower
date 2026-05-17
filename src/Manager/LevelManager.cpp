#include "Manager/LevelManager.hpp"
#include "FloorData.hpp"
#include "Block/NPC.hpp"
#include "Util/Logger.hpp"
#include "Block/Stair.hpp"
#include "Block/Wall.hpp"

LevelManager::LevelManager(std::shared_ptr<Map> map, std::shared_ptr<Player> player, Util::Renderer& renderer)
    : m_Map(map), m_Player(player), m_Renderer(&renderer) {
    // 可以在這裡初始化 m_FloorData
    m_CurrentFloor = 0;
}

void LevelManager::InitFloorData() {
    m_FloorData.clear();
    for (int i = 0; i < 27; i++) {
        std::string mapPath = std::string(RESOURCE_DIR) + "/Map/level" + std::to_string(i) + ".txt";
        m_FloorData.push_back(LoadFloorFromFile(mapPath));
    }

    // m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
    // for (auto block : m_Map->GetBlocks()) {
    //     m_Renderer->AddChild(block);
    // }
}

bool LevelManager::JumpToFloor(int targetFloor, bool checkVisited) {
    if (checkVisited && !m_FloorData[targetFloor].isVisited) return false;
    m_FloorData[m_CurrentFloor].grid = m_Map->GetLevelData();
    m_FloorData[m_CurrentFloor].isVisited = true;
    m_FloorData[m_CurrentFloor].savedNPCs.clear();
    for (auto block : m_Map->GetBlocks()) {
        if (auto npc = std::dynamic_pointer_cast<NPC>(block)) {
            m_FloorData[m_CurrentFloor].savedNPCs.push_back(npc);
        }
    }
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer->RemoveChild(block);
    }
    m_CurrentFloor = targetFloor;
    m_FloorData[m_CurrentFloor].isVisited = true;

    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);
    if (!m_FloorData[m_CurrentFloor].savedNPCs.empty()) {
        m_Map->RestoreNPCs(m_FloorData[m_CurrentFloor].savedNPCs);
    }
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer->AddChild(block);
    }
    if (targetFloor == 24 && !m_Player->GetCheatingMode()) {
        m_Player->SetItem(PlayerLabel::Item::WINDCOMPASS, false);
    }
    return true;
}

void LevelManager::ProcessStair(int stairX, int stairY) {
    const auto& stairs = m_FloorData[m_CurrentFloor].stairs;

    for (const auto& stair : stairs) {
        if (stair.x == stairX && stair.y == stairY) {
            m_Player->SetPosition(stair.targetX, stair.targetY);
            JumpToFloor(stair.targetFloor, false);
            return;
        }
    }
    LOG_ERROR("踩到樓梯，但在 TXT 檔找不到對應的座標資料！");
}

void LevelManager::ChangeRemoteBlock(int targetFloor, int x, int y, int newID) {
    if (targetFloor == m_CurrentFloor) {
        m_Map->UpdateGridID(x, y, newID);
        std::vector<std::string> floorImg = {};
        switch (newID) {
            case Config::ID::EMPTY: {
                floorImg = {RESOURCE_DIR "/Image/Road/road.bmp"};
                auto newFloor = std::make_shared<Wall>(floorImg, x, y, newID);
                newFloor->SetZIndex(5);
                m_Map->AddBlock(newFloor);
                m_Renderer->AddChild(newFloor);
                break;
            }
            case Config::ID::STAIRS_UP: {
                floorImg = {RESOURCE_DIR "/Image/Stair/upstair.bmp"};
                auto newFloor = std::make_shared<Stair>(floorImg, x, y, newID);
                newFloor->SetZIndex(5);
                m_Map->AddBlock(newFloor);
                m_Renderer->AddChild(newFloor);
                break;
            }
        }
    }
    else {
        m_FloorData[targetFloor].grid[y][x] = newID;
    }
}

void LevelManager::EnemyReinforcements(int stage) {
    int maxlevel = (stage == 1)? 16 : 21;
    for (int i = 0; i < maxlevel; i++) {
        auto map = GetFloorData()[i].grid;
        for (int j = 0; j < map.size(); j++) {
            for (int k = 0; k < map[j].size(); k++) {
                if (stage == 1) {
                    if (map[j][k] == Config::ID::SOUL_SKELETON_1) {
                        ChangeRemoteBlock(i, k, j, Config::ID::SOUL_SKELETON_2);
                    }
                    if (map[j][k] == Config::ID::DARK_KNIGHT_1) {
                        ChangeRemoteBlock(i, k, j, Config::ID::DARK_KNIGHT_2);
                    }
                    if (map[j][k] == Config::ID::DARK_MAGICIAN_1) {
                        ChangeRemoteBlock(i, k, j, Config::ID::DARK_MAGICIAN_2);
                    }
                }
                if (stage == 2) {
                    if (map[j][k] == Config::ID::SOUL_SKELETON_2) {
                        ChangeRemoteBlock(i, k, j, Config::ID::SOUL_SKELETON_3);
                    }
                    if (map[j][k] == Config::ID::DARK_KNIGHT_2) {
                        ChangeRemoteBlock(i, k, j, Config::ID::DARK_KNIGHT_3);
                    }
                    if (map[j][k] == Config::ID::DARK_MAGICIAN_2) {
                        ChangeRemoteBlock(i, k, j, Config::ID::DARK_MAGICIAN_3);
                    }
                    if (map[j][k] == Config::ID::MAGIC_SERGEANT_A_2) {
                        ChangeRemoteBlock(i, k, j, Config::ID::MAGIC_SERGEANT_A_3);
                    }
                }
            }
        }
    }
}

void LevelManager::RestoreLevelState(const std::vector<FloorData> &savedFloors, int targetFloor) {
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer->RemoveChild(block);
    }
    m_FloorData = savedFloors;
    m_CurrentFloor = targetFloor;
    m_FloorData[m_CurrentFloor].isVisited = true;

    m_Map->LoadLevel(m_FloorData[m_CurrentFloor].grid);

    if (!m_FloorData[m_CurrentFloor].savedNPCs.empty()) {
        m_Map->RestoreNPCs(m_FloorData[m_CurrentFloor].savedNPCs);
    }
    for (auto block : m_Map->GetBlocks()) {
        m_Renderer->AddChild(block);
    }
}

void LevelManager::SyncCurrentFloorState() {
    if (m_CurrentFloor < 0 || m_CurrentFloor >= m_FloorData.size()) {
        return;
    }

    m_FloorData[m_CurrentFloor].grid = m_Map->GetLevelData();

    m_FloorData[m_CurrentFloor].savedNPCs.clear();

    for (auto block : m_Map->GetBlocks()) {
        if (auto npc = std::dynamic_pointer_cast<NPC>(block)) {
            m_FloorData[m_CurrentFloor].savedNPCs.push_back(npc);
        }
    }
}

void LevelManager::CreateNPCs(FloorData &floorData) {
    std::vector<std::shared_ptr<NPC>> npcPtrs;
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            int npcID = floorData.grid[y][x];
            if (npcID >= Config::ID::NPC_BEGIN && npcID <= Config::ID::NPC_END) {
                auto npc = m_Map->LoadNPCs(npcID, x, y);
                for (int i = 0; i < floorData.npcRecords.size(); i++) {
                    if (floorData.npcRecords[i].id == npcID) {
                        npc->SetCurrentStage(floorData.npcRecords[i].currentStage);
                        for (int j = 0; j < floorData.npcRecords[i].totalStage; j++) {
                            npc->SetStageCompleted(j, floorData.npcRecords[i].stageCompleted[j]);
                        }
                    }
                }
                npcPtrs.push_back(npc);
            }
        }
    }
    floorData.savedNPCs = npcPtrs;
}