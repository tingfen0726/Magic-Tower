//
// Created by fenfenfen on 2026/3/16.
//
#include "Map.hpp"
#include "config.hpp"
#include "Block/Wall.hpp"
#include "Block/Door.hpp"
#include "Block/Stair.hpp"
#include "Block/Props.hpp"
#include <iostream>
#include <iomanip>


Map::Map(){}

void Map::LoadLevel(const std::vector<std::vector<int>>& levelData) {
    m_LevelData = levelData;
    m_Blocks.clear();
    for (int y = 0; y < m_LevelData.size(); y++) {
        for (int x = 0; x < m_LevelData[y].size(); x++) {
            int blockID = m_LevelData[y][x];
            // if (blockID==0) {continue;}

            std::vector<std::string> imagePath = {};
            switch (blockID) {
                case Config::ID::EMPTY:
                    m_Blocks.push_back(std::make_shared<Wall>(
                        std::vector<std::string>{RESOURCE_DIR "/Image/Road/road.bmp"},
                        x, y, Config::ID::EMPTY
                    ));
                    break;
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
                            RESOURCE_DIR "/Image/Door/road.bmp"
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
                            RESOURCE_DIR "/Image/Door/road.bmp"
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
                            RESOURCE_DIR "/Image/Door/road.bmp"
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
                            RESOURCE_DIR "/Image/Door/road.bmp"
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
                            RESOURCE_DIR "/Image/Door/road.bmp"
                        },
                        x, y, Config::ID::DOOR_IRON
                    ));
                    break;
                case Config::ID::STAIRS_UP:
                    m_Blocks.push_back(std::make_shared<Stair>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Stair/upstair.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::STAIRS_UP
                     ));
                    break;
                case Config::ID::STAIRS_DOWN:
                    m_Blocks.push_back(std::make_shared<Stair>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Stair/downstair.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::STAIRS_DOWN
                     ));
                    break;
                case Config::ID::YELLOW_KEY:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/yellow_key.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::YELLOW_KEY
                     ));
                    break;
                case Config::ID::BLUE_KEY:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/blue_key.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::BLUE_KEY
                     ));
                    break;
                case Config::ID::RED_KEY:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/red_key.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::RED_KEY
                     ));
                    break;
                case Config::ID::MAGIC_KEY:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/magic_key.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::MAGIC_KEY
                     ));
                    break;
                case Config::ID::RED_POTION:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/red_potion.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::RED_POTION
                     ));
                    break;
                case Config::ID::BLUE_POTION:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/blue_potion.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::BLUE_POTION
                     ));
                    break;
                case Config::ID::HOLY_WATER:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/holy_water.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::HOLY_WATER
                     ));
                    break;
                case Config::ID::RUBY:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/ruby.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::RUBY
                     ));
                    break;
                case Config::ID::SAPPHIRE:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/sapphire.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SAPPHIRE
                     ));
                    break;
                case Config::ID::SWORD_A:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/no_item.png"
                         },
                         x, y, Config::ID::SWORD_A
                     ));
                    break;
                case Config::ID::SWORD_B:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/sword_b.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SWORD_B
                     ));
                    break;
                case Config::ID::SWORD_C:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/sword_c.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SWORD_C
                     ));
                    break;
                case Config::ID::SWORD_D:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/sword_d.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SWORD_D
                     ));
                    break;
                case Config::ID::SHIELD_A:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/shield_a.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SHIELD_A
                     ));
                    break;
                case Config::ID::SHIELD_B:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/no_item.png"
                         },
                         x, y, Config::ID::SHIELD_B
                     ));
                    break;
                case Config::ID::SHIELD_C:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/shield_c.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SHIELD_C
                     ));
                    break;
                case Config::ID::SHIELD_D:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/shield_d.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SHIELD_D
                     ));
                    break;
                case Config::ID::SHIELD_E:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/no_item.png"
                         },
                         x, y, Config::ID::SHIELD_E
                     ));
                    break;
                case Config::ID::COIN:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/coin.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::COIN
                     ));
                    break;
                case Config::ID::JUMP_WING_SMALL:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/jump_wing.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::JUMP_WING_SMALL
                     ));
                    break;
                case Config::ID::JUMP_WING_BIG:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/jump_wing.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::JUMP_WING_BIG
                     ));
                    break;
                case Config::ID::HOLY_CROSS:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/holy_cross.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::HOLY_CROSS
                     ));
                    break;
                case Config::ID::RED_VERI:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/red_veri.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::RED_VERI
                     ));
                    break;
                case Config::ID::BLUE_VERI:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/no_item.png"
                         },
                         x, y, Config::ID::BLUE_VERI
                     ));
                    break;
                case Config::ID::GREEN_VERI:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/green_veri.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::GREEN_VERI
                     ));
                    break;
                case Config::ID::GOD_KNIFE_SIGN:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/god_knife_sign.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::GOD_KNIFE_SIGN
                     ));
                    break;
                case Config::ID::WIND_COMPASS:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/wind_compass.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::WIND_COMPASS
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
    std::vector<std::pair<int, int>> blocksToRemove;
    for (auto block : m_Blocks) {
        block->UpdateAnimation();

        auto door = std::dynamic_pointer_cast<Door>(block);
        if (door) {
            if (door->IsFullyOpen()) {
                auto pos = door->GetPosition();
                blocksToRemove.push_back({pos[0], pos[1]});
            }
        }

        auto props = std::dynamic_pointer_cast<Props>(block);
        if (props) {
            if (props->GetPickUp()) {
                auto pos = props->GetPosition();
                blocksToRemove.push_back({pos[0], pos[1]});
            }
        }

    }
    for (const auto& pos : blocksToRemove) {
        RemoveBlock(pos.first, pos.second);
    }
}

void Map::RemoveBlock(int x, int y) {
    if (y >= 0 && y < m_LevelData.size() && x >= 0 && x < m_LevelData[y].size()) {
        if (m_LevelData[y][x] == 0) { return; }
        m_LevelData[y][x] = 0;
    }
    for (auto& block : m_Blocks) {
        auto pos = block->GetPosition();
        if (pos[0] == x && pos[1] == y) {
            // block->SetVisible(false);
            break;
        }
    }

    for (const auto& row : m_LevelData) {
        for (int cell : row) {
            if (cell == 0) {
                std::cout << std::setw(3) << "." << " ";
            } else {
                std::cout << std::setw(3) << cell << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}


void Block::SetImageFrame(int index) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    if (temp) {
        temp->SetImage(m_imagePath[index]);
    }
}

