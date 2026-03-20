//
// Created by fenfenfen on 2026/3/19.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP

//
// Created by fenfenfen on 2026/3/19.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct FloorData {
    int floorLevel;
    std::vector<std::vector<int>> grid;
    int upStairsX, upStairsY;
    int downStairsX, downStairsY;
};
FloorData LoadFloorFromFile(const std::string& filepath);

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FLOORDATA_HPP