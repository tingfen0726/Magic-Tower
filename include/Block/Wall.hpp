#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_WALL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_WALL_HPP

#include "Map.hpp"
#include <vector>
#include <string>

class Wall : public Block {
public:
    Wall(const std::vector<std::string>& imagePath, int x, int y, int id);

    void UpdateAnimation() override;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_WALL_HPP