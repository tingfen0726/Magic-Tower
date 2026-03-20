//
// Created by fenfenfen on 2026/3/20.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PROPS_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PROPS_HPP
#include "Map.hpp"

class Props : public Block {
public:
    Props(const std::vector<std::string>& imagePath, int x, int y, int id);
    void UpdateAnimation() override;
    void PickUp() {m_IsPickUp = true;}
    bool GetPickUp() {return m_IsPickUp;}

private:
    bool m_IsPickUp = false;
};


#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PROPS_HPP