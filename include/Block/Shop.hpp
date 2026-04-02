#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SHOP_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SHOP_HPP

#include "Map.hpp"

class Shop : public Block {
public:
    Shop(const std::vector<std::string>& imagePath, int x, int y, int id);
    void UpdateAnimation() override;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SHOP_HPP