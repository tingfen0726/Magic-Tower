#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_DOOR_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_DOOR_HPP

#include "Map.hpp"
#include <vector>
#include <string>


class Door : public Block {
public:
    Door(const std::vector<std::string>& imagePath, int x, int y, int id);
    void Open();
    bool CanOpen(std::vector<int> keys);
    void UpdateAnimation() override;
    bool IsOpen() {return m_IsOpen;}
    bool IsFullyOpen() {return m_IsOpen && (m_CurrentFrame >= m_imagePath.size() - 1);}
private:
    bool m_IsOpen = false;


};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_DOOR_HPP