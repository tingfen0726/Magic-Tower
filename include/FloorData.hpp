//
// Created by fenfenfen on 2026/3/19.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP

//
// Created by fenfenfen on 2026/3/19.
//

#include <vector>
#include <string>
#include "Map.hpp"

struct StairData {
    int x;            // 出發點 X
    int y;            // 出發點 Y
    int targetFloor;  // 目標樓層
    int targetX;      // 目標 X
    int targetY;      // 目標 Y
};

struct FloorData {
    int floorLevel;
    int flyX;
    int flyY;
    std::vector<StairData> stairs;
    std::vector<std::vector<int>> grid;
    std::vector<std::shared_ptr<NPC>> savedNPCs;
    bool isVisited = false;
};
FloorData LoadFloorFromFile(const std::string& filepath);

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP