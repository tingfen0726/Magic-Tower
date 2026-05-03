//
// Created by fenfenfen on 2026/3/19.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "FloorData.hpp"

FloorData LoadFloorFromFile(const std::string& filepath) {
    FloorData data;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error: 無法開啟地圖檔案 " << filepath << std::endl;
        return data;
    }

    file >> data.floorLevel;
    file >> data.flyX >> data.flyY;

    int stairCount;
    file >> stairCount;

    for (int i = 0; i < stairCount; ++i) {
        StairData stair;
        file >> stair.x >> stair.y >> stair.targetFloor >> stair.targetX >> stair.targetY;
        data.stairs.push_back(stair);
    }

    data.grid.assign(11, std::vector<int>(11, 0));
    for (int y = 0; y < 11; ++y) {
        for (int x = 0; x < 11; ++x) {
            file >> data.grid[y][x];
        }
    }
    file.close();
    return data;
}