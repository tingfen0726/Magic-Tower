#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_ENEMYDATABASE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_ENEMYDATABASE_HPP
#include "Block/Enemy.hpp"

namespace EnemyDatabase {
    const std::unordered_map<int, EnemyStats> Data = {
        {Config::ID::GREEN_SLIME,           {50, 20, 1, 1, 1, 0}},
        {Config::ID::RED_SLIME,             {70, 15, 2, 2, 2, 0}},
        {Config::ID::BAT,                   {100, 20,  5, 3, 3, 0}},
        {Config::ID::SKELETON_C,            {110, 25, 5 ,5, 4, 0}},
        {Config::ID::BIG_SLIME,             {200, 35, 10, 5, 5, 0}},
        {Config::ID::SKELETON_B,            {150, 40, 20, 8, 6, 0}},
        {Config::ID::PRIEST_C,              {125, 50, 25, 10, 7, 0}},
        {Config::ID::BIG_BAT,               {150, 65, 30, 10, 8, 0}},
        {Config::ID::ZOMBIE,                {300, 75, 45, 13, 10, 0}},
        {Config::ID::SKELETON_A,              {400, 90, 50, 15, 12, 0}},
        {Config::ID::STONE_MONSTER_B,       {500, 115, 65, 15, 15, 0}},
        {Config::ID::MAGACIAN_B,            {250, 120, 70, 20, 17, 100}},
        {Config::ID::GATE_KEEPER_C,         {450, 150, 90, 22, 19, 0}},
        {Config::ID::RED_BAT,               {550, 160, 90, 25, 20, 0}},
        {Config::ID::PRIEST_A,                {100, 200, 110, 30, 25, 0}},
        {Config::ID::SLIME_LORD,            {700, 250, 125, 32, 30, 0}},
        {Config::ID::MAGIC_SERGEANT_D,    {1300, 300, 150, 40, 35, 0.25}},
        {Config::ID::KNIGHT,                {850, 350, 200, 45, 40, 0}},
        {Config::ID::MAGACIAN_A,              {500, 400, 260, 47, 45, 300}},
        {Config::ID::ZOMBIE_KNIGHT,         {900, 450, 330, 50, 50, 0}},
        {Config::ID::GATE_KEEPER_B,         {1250, 500, 400, 55, 55, 0}},
        {Config::ID::GATE_KEEPER_A,           {1500, 560, 460, 60, 60, 0}},
        {Config::ID::SWORDSMAN,             {1200, 620, 520, 65, 75, 0}},
        {Config::ID::SOUL_SKELETON_KNIGHT,  {2000, 680, 590, 70, 65, 0}},
        {Config::ID::IRON_KNIGHT_A,           {900, 750, 650, 77, 70, 0}},
        {Config::ID::DARK_MAGICIAN_1,       {1500, 830, 730, 80, 70, 1/3}},
        {Config::ID::DARK_MAGICIAN_2,       {2000, 1106, 973, 106, 93, 1/3}},
        {Config::ID::DARK_MAGICIAN_3,       {3000, 2212, 1946, 132, 116, 1/3}},
        {Config::ID::SOUL_SKELETON_1,       {2500, 900, 850, 84, 75, 0}},
        {Config::ID::SOUL_SKELETON_2,       {3333, 1200, 1133, 112, 100, 0}},
        {Config::ID::SOUL_SKELETON_3,       {4999, 2400, 2266, 140, 125, 0}},
        {Config::ID::DARK_KNIGHT_1,         {1200, 980, 900, 88, 75, 0}},
        {Config::ID::DARK_KNIGHT_2,         {1600, 1306, 1200, 117, 100, 0}},
        {Config::ID::DARK_KNIGHT_3,         {2400, 2612, 2400, 146, 125, 0}},
        {Config::ID::MAGIC_SERGEANT_A_1,      {15000, 1000, 1000, 100, 100, 0}},
        {Config::ID::MAGIC_SERGEANT_A_2,      {20000, 1333, 1333, 133, 133, 0}},
        {Config::ID::MAGIC_SERGEANT_A_3,      {30000, 2666, 2666, 166, 166, 0}},
        {Config::ID::SLIME_MEN,             {3100, 1150, 1050, 92, 80, 0}},
        {Config::ID::VAMPIRE_1,             {30000, 1700, 1500, 250, 220, 0}},
        {Config::ID::VAMPIRE_2,             {45000, 2550, 2250, 312, 275, 0}},
        {Config::ID::VAMPIRE_3,             {60000, 3400, 3000, 390, 343, 0}}

    };
}

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_ENEMYDATABASE_HPP