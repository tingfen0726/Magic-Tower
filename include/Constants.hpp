#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_CONSTANTS_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_CONSTANTS_HPP

namespace Config {

    inline constexpr float TILE_SIZE = 56.7f;
    inline constexpr float MAP_OFFSET_X = -141.5f;
    inline constexpr float MAP_OFFSET_Y = 283.6f;

    namespace ID {
        inline constexpr int EMPTY = 0;
        inline constexpr int WALL_BEGIN = 1;

        inline constexpr int WALL_BROWN = 1;
        inline constexpr int WALL_LAVA  = 2;
        inline constexpr int WALL_STAR  = 3;

        inline constexpr int WALL_END   = 3;


        inline constexpr int DOOR_BEGIN = 5;

        inline constexpr int DOOR_YELLOW = 5;
        inline constexpr int DOOR_BLUE = 6;
        inline constexpr int DOOR_RED = 7;
        inline constexpr int DOOR_GREEN = 8;
        inline constexpr int DOOR_IRON = 9;

        inline constexpr int DOOR_END   = 9;




        //樓梯範圍：
        inline constexpr int STAIRS_BEGIN = 30;

        inline constexpr int STAIRS_UP   = 30;
        inline constexpr int STAIRS_DOWN = 31;

        inline constexpr int STAIRS_END   = 31;

        // 怪物範圍：
        inline constexpr int ENEMY_BEGIN = 100;
        inline constexpr int ENEMY_END   = 199;

        // 道具範圍：
        inline constexpr int ITEM_BEGIN  = 200;
        inline constexpr int YELLOW_KEY = 200;
        inline constexpr int BLUE_KEY = 201;
        inline constexpr int RED_KEY = 202;
        inline constexpr int MAGIC_KEY = 203;
        inline constexpr int RED_POTION = 204;
        inline constexpr int BLUE_POTION = 205;
        inline constexpr int HOLY_WATER = 206;
        inline constexpr int RUBY = 207;
        inline constexpr int SAPPHIRE = 208;
        inline constexpr int SWORD_A = 209;
        inline constexpr int SWORD_B = 210;
        inline constexpr int SWORD_C = 211;
        inline constexpr int SWORD_D = 212;
        inline constexpr int SHIELD_A = 213;
        inline constexpr int SHIELD_B = 214;
        inline constexpr int SHIELD_C = 215;
        inline constexpr int SHIELD_D = 216;
        inline constexpr int SHIELD_E = 217;
        inline constexpr int COIN = 218;
        inline constexpr int JUMP_WING_SMALL = 219;
        inline constexpr int JUMP_WING_BIG = 220;
        inline constexpr int HOLY_CROSS = 221;
        inline constexpr int RED_VERI = 222;
        inline constexpr int BLUE_VERI = 223;
        inline constexpr int GREEN_VERI = 224;
        inline constexpr int GOD_KNIFE_SIGN = 225;
        inline constexpr int WIND_COMPASS = 226;
        inline constexpr int ITEM_END    = 299;

        // 門的範圍：
        // inline constexpr int DOOR_BEGIN  = 300;
        // inline constexpr int DOOR_END    = 399;

        // NPC範圍：
        inline constexpr int NPC_BEGIN   = 400;
        inline constexpr int NPC_END     = 499;
    }
}


#endif //REPLACE_WITH_YOUR_PROJECT_NAME_CONSTANTS_HPP