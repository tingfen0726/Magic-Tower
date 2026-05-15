#include "Manager/SaveManager.hpp"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

#include "Block/NPC.hpp"

SaveManager::SaveManager(std::shared_ptr<LevelManager> levelManager, std::shared_ptr<Player> player)
: m_levelManager(levelManager), m_Player(player) {

}

std::string SaveManager::GetCurrentTimeString() {
    auto now = std::chrono::system_clock::now();

    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm* now_tm = std::localtime(&now_c);

    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y%m%d_%H%M%S");
    return ss.str();
}

bool SaveManager::SaveGame() {
    m_levelManager->SyncCurrentFloorState();
    std::string saveDirectory = std::string(RESOURCE_DIR) + "/SaveData";

    std::string timeString = GetCurrentTimeString();
    std::string filename = saveDirectory + "/Save_" + timeString + ".txt";

    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: 無法建立存檔 " << filename << std::endl;
        return false;
    }

    file << "[Player]\n";
    file << m_Player->GetPlayerStats().level << " "
    << m_Player->GetPlayerStats().hp << " "
    << m_Player->GetPlayerStats().atk << " "
    << m_Player->GetPlayerStats().def << " "
    << m_Player->GetPlayerStats().gold << " "
    << m_Player->GetPlayerStats().exp << "\n";

    file << m_Player->GetInventory().yellowKey << " "
    << m_Player->GetInventory().blueKey << " "
    << m_Player->GetInventory().redKey << " "
    << m_Player->GetInventory().hasholyCross << " "
    << m_Player->GetInventory().hasredveri << " "
    << m_Player->GetInventory().hasblueveri << " "
    << m_Player->GetInventory().hasgreenveri << " "
    << m_Player->GetInventory().hasgemhoe<< " "
    << m_Player->GetInventory().hasgodknifesign << " "
    << m_Player->GetInventory().haswindCompass << "\n";

    file << m_Player->GetCurrentGridX() << " " << m_Player->GetCurrentGridY() << "\n";
    file << m_Player->GetCheatingMode() << "\n";

    file << "\n[Map]\n";

    std::vector<FloorData>& floors = m_levelManager->GetFloorData();
    int currentFloor = m_levelManager->GetCurrentFloor();

    file << currentFloor << "\n";
    file << floors.size() << "\n";

    for (const auto& data : floors) {
        file << "\n" << data.floorLevel << "\n";
        file << data.flyX << " " << data.flyY << "\n";

        file << data.stairs.size() << "\n";
        for (const auto& stair : data.stairs) {
            file << stair.x << " " << stair.y << " "
                 << stair.targetFloor << " " << stair.targetX << " " << stair.targetY << "\n";
        }

        for (int y = 0; y < 11; ++y) {
            for (int x = 0; x < 11; ++x) {
                file << data.grid[y][x] << " ";
            }
            file << "\n";
        }
        file << "\n["<< data.floorLevel << "NPC" << "]\n";
        file << data.savedNPCs.size() << "\n";
        for (const auto& npc : data.savedNPCs) {
            file << npc->GetID() << " " << npc->GetCurrentStage() << " " << npc->GetDialogues().size() <<"\n";
            for (int i = 0; i < npc->GetDialogues().size(); i++) {
                file << npc->GetStageCompleted(i) <<" ";
            }
            file << "\n";
        }
        file << data.isVisited <<"\n";
    }
    file << "\n";

    file.close();
    std::cout << "遊戲存檔成功：" << filename << std::endl;
    return true;
}

bool SaveManager::LoadGame(const std::string& filename, GameSaveData& data) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: 無法開啟存檔 " << filename << std::endl;
        return false;
    }

    std::string header;

    file >> header; // 讀掉 "[Player]"
    file >> data.player_stats.level
    >> data.player_stats.hp
    >> data.player_stats.atk
    >> data.player_stats.def
    >> data.player_stats.gold
    >> data.player_stats.exp;

    file >> data.player_inventory.yellowKey
    >> data.player_inventory.blueKey
    >> data.player_inventory.redKey
    >> data.player_inventory.hasholyCross
    >> data.player_inventory.hasredveri
    >> data.player_inventory.hasblueveri
    >> data.player_inventory.hasgreenveri
    >> data.player_inventory.hasgemhoe
    >> data.player_inventory.hasgodknifesign
    >> data.player_inventory.haswindCompass;

    file >> data.playerGridX >> data.playerGridY;
    file >> data.Cheating_Mode;

    file >> header;

    file >> data.m_CurrentFloor;
    int foolrs = 0;
    file >> foolrs;

    for (int i = 0; i < foolrs; i++) {
        FloorData floordata;
        file >> floordata.floorLevel;
        file >> floordata.flyX >> floordata.flyY;

        int stairs;
        file >> stairs;
        for (int j = 0; j < stairs; j++) {
            StairData stair;
            file >> stair.x >> stair.y >> stair.targetFloor >> stair.targetX >> stair.targetY;
            floordata.stairs.push_back(stair);
        }
        floordata.grid.assign(11, std::vector<int>(11, 0));
        for (int y = 0; y < 11; ++y) {
            for (int x = 0; x < 11; ++x) {
                file >> floordata.grid[y][x];
            }
        }
        file >> header;
        int npcCount;
        file >> npcCount;

        for (int j = 0; j < npcCount; j++) {
            NPCSaveRecord npcRecord;
            file >> npcRecord.id >> npcRecord.currentStage >> npcRecord.totalStage;
            for (int k = 0; k < npcRecord.totalStage; k++) {
                bool completed;
                file >> completed;
                npcRecord.stageCompleted.push_back(completed);
            }
            floordata.npcRecords.push_back(npcRecord);
        }
        file >> floordata.isVisited;
        data.m_FloorData.push_back(floordata);
    }

    file.close();
    return true;
}

