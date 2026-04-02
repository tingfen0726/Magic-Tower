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
        inline constexpr int GREEN_SLIME = 100;
        inline constexpr int RED_SLIME = 101;
        inline constexpr int BAT = 102;
        inline constexpr int SKELETON_C = 103;
        inline constexpr int BIG_SLIME = 104;
        inline constexpr int SKELETON_B = 105;
        inline constexpr int PRIEST_C = 106;
        inline constexpr int BIG_BAT = 107;
        inline constexpr int ZOMBIE = 108;
        inline constexpr int SKELETON_A = 109;
        inline constexpr int STONE_MONSTER_B = 110;
        inline constexpr int MAGACIAN_B = 111;
        inline constexpr int GATE_KEEPER_C = 112;
        inline constexpr int RED_BAT = 113;
        inline constexpr int PRIEST_A = 114;
        inline constexpr int SLIME_LORD = 115;
        inline constexpr int MAGIC_SERGEANT_D = 116;
        inline constexpr int KNIGHT = 117;
        inline constexpr int MAGACIAN_A = 118;
        inline constexpr int ZOMBIE_KNIGHT = 119;
        inline constexpr int GATE_KEEPER_B = 120;
        inline constexpr int GATE_KEEPER_A = 121;
        inline constexpr int SWORDSMAN = 122;
        inline constexpr int SOUL_SKELETON_KNIGHT = 123;
        inline constexpr int IRON_KNIGHT_A = 124;
        inline constexpr int DARK_MAGICIAN_1 = 125;
        inline constexpr int DARK_MAGICIAN_2 = 126;
        inline constexpr int DARK_MAGICIAN_3 = 127;
        inline constexpr int SOUL_SKELETON_1 = 128;
        inline constexpr int SOUL_SKELETON_2 = 129;
        inline constexpr int SOUL_SKELETON_3 = 130;
        inline constexpr int DARK_KNIGHT_1 = 131;
        inline constexpr int DARK_KNIGHT_2 = 132;
        inline constexpr int DARK_KNIGHT_3 = 133;
        inline constexpr int MAGIC_SERGEANT_A_1 = 134;
        inline constexpr int MAGIC_SERGEANT_A_2 = 135;
        inline constexpr int MAGIC_SERGEANT_A_3 = 136;
        inline constexpr int SLIME_MEN = 137;
        inline constexpr int VAMPIRE_1 = 138;
        inline constexpr int VAMPIRE_2 = 139;
        inline constexpr int VAMPIRE_3 = 140;
        inline constexpr int OCTOPUS = 141;
        inline constexpr int DRAGON = 142;
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
        inline constexpr int SWORD_E = 213;
        inline constexpr int SHIELD_A = 214;
        inline constexpr int SHIELD_B = 215;
        inline constexpr int SHIELD_C = 216;
        inline constexpr int SHIELD_D = 217;
        inline constexpr int SHIELD_E = 218;
        inline constexpr int COIN = 219;
        inline constexpr int JUMP_WING_SMALL = 220;
        inline constexpr int JUMP_WING_BIG = 221;
        inline constexpr int HOLY_CROSS = 222;
        inline constexpr int RED_VERI = 223;
        inline constexpr int BLUE_VERI = 224;
        inline constexpr int GREEN_VERI = 225;
        inline constexpr int GOD_KNIFE_SIGN = 226;
        inline constexpr int WIND_COMPASS = 227;
        inline constexpr int ITEM_END    = 299;

        // NPC範圍：
        inline constexpr int NPC_BEGIN   = 400;
        inline constexpr int NPC_END     = 499;

        //Shop範圍:
        inline constexpr int SHOP_BEGIN  = 500;
        inline constexpr int SHOP_EVEMY_10 = 510;   //怪物商店
        inline constexpr int SHOP_EVEMY_11 = 511;
        inline constexpr int SHOP_EVEMY_12 = 512;
        inline constexpr int SHOP_EXP_2 = 520;      //精驗老人
        inline constexpr int SHOP_KEY_3 = 530;      //鑰匙商人
        inline constexpr int SHOP_EVEMY_40 = 540;   //怪物商店
        inline constexpr int SHOP_EVEMY_41 = 541;
        inline constexpr int SHOP_EVEMY_42 = 542;
        inline constexpr int SHOP_KEY_5 = 550;      //鑰匙商人
        inline constexpr int SHOP_ELDER_6 =  560;   //老人
        inline constexpr int SHOP_END     = 599;
    }
}


#endif //REPLACE_WITH_YOUR_PROJECT_NAME_CONSTANTS_HPP