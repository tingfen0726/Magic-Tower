//
// Created by fenfenfen on 2026/3/16.
//
#include "Map.hpp"
#include "Constants.hpp"
#include "config.hpp"
#include "Block/Wall.hpp"
#include "Block/Door.hpp"


Map::Map(){}

void Map::LoadLevel(const std::vector<std::vector<int>>& levelData) {
    m_LevelData = levelData;
    m_Blocks.clear();
    for (int y = 0; y < m_LevelData.size(); y++) {
        for (int x = 0; x < m_LevelData[y].size(); x++) {
            int blockID = m_LevelData[y][x];
            if (blockID==0) {continue;}

            std::vector<std::string> imagePath = {};
            switch (blockID) {
                case Config::ID::WALL_BROWN:
                    m_Blocks.push_back(std::make_shared<Wall>(
                        std::vector<std::string>{RESOURCE_DIR "/Image/Road/wall_b.bmp"},
                        x, y, Config::ID::WALL_BROWN
                    ));
                    break;
                case Config::ID::WALL_LAVA:
                    m_Blocks.push_back(std::make_shared<Wall>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Road/lava.bmp",
                            RESOURCE_DIR "/Image/Road/lava2.bmp"
                        },
                        x, y, Config::ID::WALL_LAVA
                    ));
                    break;
                case Config::ID::WALL_STAR:
                    m_Blocks.push_back(std::make_shared<Wall>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Road/wall_shine.bmp",
                            RESOURCE_DIR "/Image/Road/wall_shine2.bmp"
                        },
                        x, y, Config::ID::WALL_STAR
                    ));
                    break;

                case Config::ID::DOOR_YELLOW:
                    m_Blocks.push_back(std::make_shared<Door>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Door/yellow_door.bmp",
                            RESOURCE_DIR "/Image/Door/yellow_door2.bmp",
                            RESOURCE_DIR "/Image/Door/yellow_door3.bmp",
                            RESOURCE_DIR "/Image/Door/yellow_door4.bmp",
                            RESOURCE_DIR "/Image/Door/yellow_door5.bmp",
                            RESOURCE_DIR "/Image/Door/no_door.png"
                        },
                        x, y, Config::ID::DOOR_YELLOW
                    ));
                    break;
                case Config::ID::DOOR_BLUE:
                    m_Blocks.push_back(std::make_shared<Door>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Door/blue_door.bmp",
                            RESOURCE_DIR "/Image/Door/blue_door2.bmp",
                            RESOURCE_DIR "/Image/Door/blue_door3.bmp",
                            RESOURCE_DIR "/Image/Door/blue_door4.bmp",
                            RESOURCE_DIR "/Image/Door/blue_door5.bmp",
                            RESOURCE_DIR "/Image/Door/no_door.png"
                        },
                        x, y, Config::ID::DOOR_BLUE
                    ));
                    break;
                case Config::ID::DOOR_RED:
                    m_Blocks.push_back(std::make_shared<Door>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Door/red_door.bmp",
                            RESOURCE_DIR "/Image/Door/red_door2.bmp",
                            RESOURCE_DIR "/Image/Door/red_door3.bmp",
                            RESOURCE_DIR "/Image/Door/red_door4.bmp",
                            RESOURCE_DIR "/Image/Door/red_door5.bmp",
                            RESOURCE_DIR "/Image/Door/no_door.png"
                        },
                        x, y, Config::ID::DOOR_RED
                    ));
                    break;
                case Config::ID::DOOR_GREEN:
                    m_Blocks.push_back(std::make_shared<Door>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Door/green_door.bmp",
                            RESOURCE_DIR "/Image/Door/green_door2.bmp",
                            RESOURCE_DIR "/Image/Door/green_door3.bmp",
                            RESOURCE_DIR "/Image/Door/green_door4.bmp",
                            RESOURCE_DIR "/Image/Door/green_door5.bmp",
                            RESOURCE_DIR "/Image/Door/no_door.png"
                        },
                        x, y, Config::ID::DOOR_GREEN
                    ));
                    break;
                case Config::ID::DOOR_IRON:
                    m_Blocks.push_back(std::make_shared<Door>(
                        std::vector<std::string>{
                            RESOURCE_DIR "/Image/Door/iron_fence.bmp",
                            RESOURCE_DIR "/Image/Door/iron_fence2.bmp",
                            RESOURCE_DIR "/Image/Door/iron_fence3.bmp",
                            RESOURCE_DIR "/Image/Door/iron_fence4.bmp",
                            RESOURCE_DIR "/Image/Door/iron_fence5.bmp",
                            RESOURCE_DIR "/Image/Door/no_door.png"
                        },
                        x, y, Config::ID::DOOR_IRON
                    ));
                    break;
                default:
                    continue;
            }
        }
    }
}

void Map::SetVisible(bool visible) {
    for (auto block : m_Blocks) {
        block->SetVisible(visible);
    }
}

void Map::Update() {
    for (auto block : m_Blocks) {
        block->UpdateAnimation();
    }
}

void Block::SetImageFrame(int index) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    if (temp) {
        temp->SetImage(m_imagePath[index]);
    }
}

