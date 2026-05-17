#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SAVEMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SAVEMANAGER_HPP

#include "LevelManager.hpp"
#include "GameSaveData.hpp"
#include "Player.hpp"

class SaveManager {
public:
    SaveManager(std::shared_ptr<LevelManager> levelManager, std::shared_ptr<Player> player);
    std::string GetCurrentTimeString();

    bool SaveGame();
    bool LoadGame(const std::string& filename, GameSaveData& outData);
    std::vector<std::string> GetLatestSaveFiles();

private:
    std::shared_ptr<LevelManager> m_levelManager;
    std::shared_ptr<Player> m_Player;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SAVEMANAGER_HPP