//
// Created by fenfenfen on 2026/3/16.
//
#include "Map.hpp"
#include "config.hpp"
#include "Block/Wall.hpp"
#include "Block/Door.hpp"
#include "Block/Stair.hpp"
#include "Block/Props.hpp"
#include "Block/Enemy.hpp"
#include "Block/Shop.hpp"
#include "Block/SpecificNPCs.hpp"
#include <iostream>
#include <iomanip>


Map::Map(){}

void Map::LoadLevel(const std::vector<std::vector<int>>& levelData) {
    m_LevelData = levelData;
    m_Blocks.clear();
    for (int y = 0; y < m_LevelData.size(); y++) {
        for (int x = 0; x < m_LevelData[y].size(); x++) {
            int blockID = m_LevelData[y][x];

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
                             RESOURCE_DIR "/Image/Stair/upstair.bmp"
                         },
                         x, y, Config::ID::STAIRS_UP
                     ));
                    break;
                case Config::ID::STAIRS_DOWN:
                    m_Blocks.push_back(std::make_shared<Stair>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Stair/downstair.bmp"
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
                case Config::ID::SWORD_E:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::SWORD_E
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
                             RESOURCE_DIR "/Image/Item/jump_wing_1.bmp",
                             RESOURCE_DIR "/Image/Item/jump_wing_2.bmp",
                             RESOURCE_DIR "/Image/Item/jump_wing_3.bmp",
                             RESOURCE_DIR "/Image/Item/jump_wing_4.bmp",
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
                case Config::ID::GEM_HOE:
                    m_Blocks.push_back(std::make_shared<Props>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Item/gem_hoe.bmp",
                             RESOURCE_DIR "/Image/Item/road.bmp"
                         },
                         x, y, Config::ID::GEM_HOE
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
                // 怪物
                case Config::ID::GREEN_SLIME:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/green_slime.bmp",
                             RESOURCE_DIR "/Image/Enemy/green_slime2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::GREEN_SLIME
                     ));
                    break;
                case Config::ID::RED_SLIME:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/red_slime.bmp",
                             RESOURCE_DIR "/Image/Enemy/red_slime2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::RED_SLIME
                     ));
                    break;
                case Config::ID::BAT:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/bat.bmp",
                             RESOURCE_DIR "/Image/Enemy/bat2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::BAT
                     ));
                    break;
                case Config::ID::SKELETON_C:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/skeleton_c.bmp",
                             RESOURCE_DIR "/Image/Enemy/skeleton_c2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SKELETON_C
                     ));
                    break;
                case Config::ID::BIG_SLIME:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/big_slime.bmp",
                             RESOURCE_DIR "/Image/Enemy/big_slime2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::BIG_SLIME
                     ));
                    break;
                case Config::ID::SKELETON_B:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/skeleton_b.bmp",
                             RESOURCE_DIR "/Image/Enemy/skeleton_b2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SKELETON_B
                     ));
                    break;
                case Config::ID::PRIEST_C:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/priest_c.bmp",
                             RESOURCE_DIR "/Image/Enemy/priest_c2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::PRIEST_C
                     ));
                    break;
                case Config::ID::BIG_BAT:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/big_bat.bmp",
                             RESOURCE_DIR "/Image/Enemy/big_bat2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::BIG_BAT
                     ));
                    break;
                case Config::ID::ZOMBIE:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/zombie.bmp",
                             RESOURCE_DIR "/Image/Enemy/zombie2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::ZOMBIE
                     ));
                    break;
                case Config::ID::SKELETON_A:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/skeleton_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/skeleton_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SKELETON_A
                     ));
                    break;
                case Config::ID::STONE_MONSTER_B:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/stone_monster_b.bmp",
                             RESOURCE_DIR "/Image/Enemy/stone_monster_b2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::STONE_MONSTER_B
                     ));
                    break;
                case Config::ID::MAGACIAN_B:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/magacian_b.bmp",
                             RESOURCE_DIR "/Image/Enemy/magacian_b2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::MAGACIAN_B
                     ));
                    break;
                case Config::ID::GATE_KEEPER_C:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/gate_keeper_c.bmp",
                             RESOURCE_DIR "/Image/Enemy/gate_keeper_c2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::GATE_KEEPER_C
                     ));
                    break;
                case Config::ID::RED_BAT:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/red_bat.bmp",
                             RESOURCE_DIR "/Image/Enemy/red_bat2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::RED_BAT
                     ));
                    break;
                case Config::ID::PRIEST_A:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/priest_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/priest_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::PRIEST_A
                     ));
                    break;
                case Config::ID::SLIME_LORD:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/slime_lord.bmp",
                             RESOURCE_DIR "/Image/Enemy/slime_lord2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SLIME_LORD
                     ));
                    break;
                case Config::ID::MAGIC_SERGEANT_D:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_d.bmp",
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_d2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::MAGIC_SERGEANT_D
                     ));
                    break;
                case Config::ID::KNIGHT:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/knight.bmp",
                             RESOURCE_DIR "/Image/Enemy/knight2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::KNIGHT
                     ));
                    break;
                case Config::ID::MAGACIAN_A:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/magacian_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/magacian_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::MAGACIAN_A
                     ));
                    break;
                case Config::ID::ZOMBIE_KNIGHT:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/zombie_knight.bmp",
                             RESOURCE_DIR "/Image/Enemy/zombie_knight2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::ZOMBIE_KNIGHT
                     ));
                    break;
                case Config::ID::GATE_KEEPER_B:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/gate_keeper_b.bmp",
                             RESOURCE_DIR "/Image/Enemy/gate_keeper_b2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::GATE_KEEPER_B
                     ));
                    break;
                case Config::ID::GATE_KEEPER_A:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/gate_keeper_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/gate_keeper_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::GATE_KEEPER_A
                     ));
                    break;
                case Config::ID::SWORDSMAN:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/swordsman.bmp",
                             RESOURCE_DIR "/Image/Enemy/swordsman2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SWORDSMAN
                     ));
                    break;
                case Config::ID::SOUL_SKELETON_KNIGHT:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton_knight.bmp",
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton_knight2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SOUL_SKELETON_KNIGHT
                     ));
                    break;
                case Config::ID::IRON_KNIGHT_A:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/iron_knight_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/iron_knight_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::IRON_KNIGHT_A
                     ));
                    break;
                case Config::ID::DARK_MAGICIAN_1:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/dark_magician.bmp",
                             RESOURCE_DIR "/Image/Enemy/dark_magician2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::DARK_MAGICIAN_1
                     ));
                    break;
                case Config::ID::DARK_MAGICIAN_2:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/dark_magician.bmp",
                             RESOURCE_DIR "/Image/Enemy/dark_magician2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::DARK_MAGICIAN_2
                     ));
                    break;
                case Config::ID::DARK_MAGICIAN_3:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/dark_magician.bmp",
                             RESOURCE_DIR "/Image/Enemy/dark_magician2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::DARK_MAGICIAN_3
                     ));
                    break;
                case Config::ID::SOUL_SKELETON_1:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton.bmp",
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SOUL_SKELETON_1
                     ));
                    break;
                case Config::ID::SOUL_SKELETON_2:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton.bmp",
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SOUL_SKELETON_2
                     ));
                    break;
                case Config::ID::SOUL_SKELETON_3:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton.bmp",
                             RESOURCE_DIR "/Image/Enemy/soul_skeleton2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SOUL_SKELETON_3
                     ));
                    break;
                case Config::ID::DARK_KNIGHT_1:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/dark_knight.bmp",
                             RESOURCE_DIR "/Image/Enemy/dark_knight2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::DARK_KNIGHT_1
                     ));
                    break;
                case Config::ID::DARK_KNIGHT_2:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/dark_knight.bmp",
                             RESOURCE_DIR "/Image/Enemy/dark_knight2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::DARK_KNIGHT_2
                     ));
                    break;
                case Config::ID::DARK_KNIGHT_3:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/dark_knight.bmp",
                             RESOURCE_DIR "/Image/Enemy/dark_knight2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::DARK_KNIGHT_3
                     ));
                    break;
                case Config::ID::MAGIC_SERGEANT_A_1:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::MAGIC_SERGEANT_A_1
                     ));
                    break;
                case Config::ID::MAGIC_SERGEANT_A_2:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::MAGIC_SERGEANT_A_2
                     ));
                    break;
                case Config::ID::MAGIC_SERGEANT_A_3:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_a.bmp",
                             RESOURCE_DIR "/Image/Enemy/magic_sergeant_a2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::MAGIC_SERGEANT_A_3
                     ));
                    break;
                case Config::ID::SLIME_MEN:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/slime_men.bmp",
                             RESOURCE_DIR "/Image/Enemy/slime_men2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::SLIME_MEN
                     ));
                    break;
                case Config::ID::VAMPIRE_1:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/vampire.bmp",
                             RESOURCE_DIR "/Image/Enemy/vampire2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::VAMPIRE_1
                     ));
                    break;
                case Config::ID::VAMPIRE_2:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/vampire.bmp",
                             RESOURCE_DIR "/Image/Enemy/vampire2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::VAMPIRE_2
                     ));
                    break;
                case Config::ID::VAMPIRE_3:
                    m_Blocks.push_back(std::make_shared<Enemy>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Enemy/vampire.bmp",
                             RESOURCE_DIR "/Image/Enemy/vampire2.bmp",
                             RESOURCE_DIR "/Image/Enemy/road.bmp"
                         },
                         x, y, Config::ID::VAMPIRE_3
                     ));
                    break;
                case Config::ID::SHOP_EVEMY_10:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shop_1_1.bmp",
                             RESOURCE_DIR "/Image/Shop/shop_1_12.bmp"
                         },
                         x, y, Config::ID::SHOP_EVEMY_10
                     ));
                    break;
                case Config::ID::SHOP_EVEMY_11:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shop_1_2.bmp",
                             RESOURCE_DIR "/Image/Shop/shop_1_22.bmp"
                         },
                         x, y, Config::ID::SHOP_EVEMY_11
                     ));
                    break;
                case Config::ID::SHOP_EVEMY_12:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shop_1_3.bmp",
                             RESOURCE_DIR "/Image/Shop/shop_1_32.bmp"
                         },
                         x, y, Config::ID::SHOP_EVEMY_12
                     ));
                    break;
                case Config::ID::SHOP_EXP_2:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/elder.bmp",
                             RESOURCE_DIR "/Image/Shop/elder2.bmp"
                         },
                         x, y, Config::ID::SHOP_EXP_2
                     ));
                    break;
                case Config::ID::SHOP_KEY_3:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shopkeeper.bmp",
                             RESOURCE_DIR "/Image/Shop/shopkeeper2.bmp"
                         },
                         x, y, Config::ID::SHOP_KEY_3
                     ));
                    break;
                case Config::ID::SHOP_EVEMY_40:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shop_1_1.bmp",
                             RESOURCE_DIR "/Image/Shop/shop_1_12.bmp"
                         },
                         x, y, Config::ID::SHOP_EVEMY_40
                     ));
                    break;
                case Config::ID::SHOP_EVEMY_41:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shop_1_2.bmp",
                             RESOURCE_DIR "/Image/Shop/shop_1_22.bmp"
                         },
                         x, y, Config::ID::SHOP_EVEMY_41
                     ));
                    break;
                case Config::ID::SHOP_EVEMY_42:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shop_1_3.bmp",
                             RESOURCE_DIR "/Image/Shop/shop_1_32.bmp"
                         },
                         x, y, Config::ID::SHOP_EVEMY_42
                     ));
                    break;
                case Config::ID::SHOP_KEY_5:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/shopkeeper.bmp",
                             RESOURCE_DIR "/Image/Shop/shopkeeper2.bmp"
                         },
                         x, y, Config::ID::SHOP_KEY_5
                     ));
                    break;
                case Config::ID::SHOP_ELDER_6:
                    m_Blocks.push_back(std::make_shared<Shop>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/Shop/elder.bmp",
                             RESOURCE_DIR "/Image/Shop/elder2.bmp"
                         },
                         x, y, Config::ID::SHOP_ELDER_6
                     ));
                    break;
                case Config::ID::FAIRY_0:
                    m_Blocks.push_back(std::make_shared<FairyNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/fairy.bmp",
                             RESOURCE_DIR "/Image/NPC/fairy2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::FAIRY_0
                     ));
                    break;
                case Config::ID::THIEF_4:
                    m_Blocks.push_back(std::make_shared<ThiefNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/thief.bmp",
                             RESOURCE_DIR "/Image/NPC/thief2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::THIEF_4
                     ));
                    break;
                case Config::ID::ELDER_2:
                    m_Blocks.push_back(std::make_shared<DonorNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/elder.bmp",
                             RESOURCE_DIR "/Image/NPC/elder2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::ELDER_2
                     ));
                    break;
                case Config::ID::SHOPKEEPER_2:
                    m_Blocks.push_back(std::make_shared<DonorNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/shopkeeper.bmp",
                             RESOURCE_DIR "/Image/NPC/shopkeeper2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::SHOPKEEPER_2
                     ));
                    break;
                case Config::ID::SHOPKEEPER_15:
                    m_Blocks.push_back(std::make_shared<TraderNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/shopkeeper.bmp",
                             RESOURCE_DIR "/Image/NPC/shopkeeper2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::SHOPKEEPER_15
                     ));
                    break;
                case Config::ID::ELDER_15:
                    m_Blocks.push_back(std::make_shared<TraderNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/elder.bmp",
                             RESOURCE_DIR "/Image/NPC/elder2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::ELDER_15
                     ));
                    break;
                case Config::ID::ELDER_16:
                    m_Blocks.push_back(std::make_shared<ElderNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/elder.bmp",
                             RESOURCE_DIR "/Image/NPC/elder2.bmp",
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::ELDER_16
                     ));
                    break;
                case Config::ID::PRINCESS:
                    m_Blocks.push_back(std::make_shared<princessNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/princess.bmp",
                             RESOURCE_DIR "/Image/NPC/princess2.bmp"
                         },
                         x, y, Config::ID::PRINCESS
                     ));
                    break;
                case Config::ID::VAMPIRE_19:
                    m_Blocks.push_back(std::make_shared<vampireNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/road.bmp"
                         },
                         x, y, Config::ID::VAMPIRE_19
                     ));
                    break;

                case Config::ID::SYSTEM_NPC:
                    m_Blocks.push_back(std::make_shared<systemNPC>(
                         std::vector<std::string>{
                             RESOURCE_DIR "/Image/NPC/system.bmp",
                         },
                         x, y, Config::ID::SYSTEM_NPC
                     ));
                    break;
                default:
                    continue;
            }
        }
    }
}

void Map::RestoreNPCs(const std::vector<std::shared_ptr<NPC>>& savedNPCs) {
    for (size_t i = 0; i < m_Blocks.size(); i++) {
        if (auto freshNpc = std::dynamic_pointer_cast<NPC>(m_Blocks[i])) {
            for (auto oldNpc : savedNPCs) {
                if (freshNpc->GetID() == oldNpc->GetID() &&
                    freshNpc->GetPosition() == oldNpc->GetPosition()) {
                    m_Blocks[i] = oldNpc;
                    break;
                    }
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
    std::vector<std::shared_ptr<Block>> blocksToRemove;
    for (auto block : m_Blocks) {
        block->UpdateAnimation();

        auto door = std::dynamic_pointer_cast<Door>(block);
        if (door) {
            if (door->IsFullyOpen()) {
                auto pos = door->GetPosition();
                blocksToRemove.push_back(block);
            }
        }

        auto props = std::dynamic_pointer_cast<Props>(block);
        if (props) {
            if (props->GetPickUp()) {
                auto pos = props->GetPosition();
                blocksToRemove.push_back(block);
            }
        }
        auto enemy = std::dynamic_pointer_cast<Enemy>(block);
        if (enemy) {
            if (enemy->GetIsdie()) {
                auto pos = enemy->GetPosition();
                blocksToRemove.push_back(block);
            }
        }
        auto npc = std::dynamic_pointer_cast<NPC>(block);
        if (npc) {
            auto stages = npc->GetDialogues();
            if (!stages.empty()) {
                bool isLastTextFinished = (npc->GetCurrentStage() == stages.size() - 1) && stages.back().isCompleted;
                if (isLastTextFinished && !npc->GetIsPersistent()) {
                    auto pos = npc->GetPosition();
                    blocksToRemove.push_back(block);
                }
            }
        }

    }
    for (auto block : blocksToRemove) {
        RemoveBlock(block);
    }
}

void Map::RemoveBlock(std::shared_ptr<Block> blocksToRemove) {
    auto pos = blocksToRemove->GetPosition();
    int x = pos[0];
    int y = pos[1];
    if (y >= 0 && y < m_LevelData.size() && x >= 0 && x < m_LevelData[y].size()) {
        if (m_LevelData[y][x] == 0) { return; }
        if (m_LevelData[y][x] == blocksToRemove->GetID()) {
            m_LevelData[y][x] = 0;
        }
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
    std::cout << "-------------------------------------------" << std::endl;
}

void Map::MoveNPC(std::shared_ptr<NPC> npcPtr, int nextX, int nextY) {
    int oldX = npcPtr->GetPosition()[0];
    int oldY = npcPtr->GetPosition()[1];
    m_LevelData[oldY][oldX] = 0;
    m_LevelData[nextY][nextX] = npcPtr->GetID();
    npcPtr->SetPosition(nextX, nextY);
}


void Block::SetImageFrame(int index) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    if (temp) {
        temp->SetImage(m_imagePath[index]);
    }
}

void Map::UpdateGridID(int x, int y, int newID) {
    if (y >= 0 && y < m_LevelData.size() && x >= 0 && x < m_LevelData[0].size()) {
        m_LevelData[y][x] = newID;
    }
}
