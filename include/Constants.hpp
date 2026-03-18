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

        inline constexpr int Stairs = 4;

        inline constexpr int DOOR_BEGIN = 5;

        inline constexpr int DOOR_YELLOW = 5;
        inline constexpr int DOOR_RED = 6;
        inline constexpr int DOOR_BLUE = 7;
        inline constexpr int DOOR_GREEN = 8;
        inline constexpr int DOOR_IRON = 9;

        inline constexpr int DOOR_END   = 9;




        //樓梯範圍：
        inline constexpr int STAIRS_BEGIN = 30;

        inline constexpr int STAIRS_UP   = 30;
        inline constexpr int STAIRS_DOWN = 31;

        inline constexpr int STAIRS_END   = 39;

        // 怪物範圍：
        inline constexpr int ENEMY_BEGIN = 100;
        inline constexpr int ENEMY_END   = 199;

        // 道具範圍：
        inline constexpr int ITEM_BEGIN  = 200;
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