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

struct FloorData {
    int floorLevel;
    std::vector<std::vector<int>> grid;
    std::vector<std::shared_ptr<NPC>> savedNPCs;
    int upStairsX, upStairsY;
    int downStairsX, downStairsY;
    bool isVisited = false;
};
FloorData LoadFloorFromFile(const std::string& filepath);

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP