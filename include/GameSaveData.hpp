#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SAVEDATA_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SAVEDATA_HPP

#include <vector>
#include <string>
#include "Player.hpp"
#include "FloorData.hpp"


struct GameSaveData {
    PlayerStats player_stats;
    PlayerInventory player_inventory;
    std::vector<FloorData> m_FloorData;
    int m_CurrentFloor;
    int playerGridX;
    int playerGridY;
    bool Cheating_Mode;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SAVEDATA_HPP