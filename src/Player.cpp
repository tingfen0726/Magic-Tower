#include "Player.hpp"
#include "Util/Time.hpp"
#include "Constants.hpp"
#include "Block/Door.hpp"

Player::Player() : Character(RESOURCE_DIR "/Image/Player/player_11.BMP", 100.0f) {
    m_Direction = 1;
    m_CurrentGridX = 5;
    m_CurrentGridY = 10;
    m_Transform.translation = {141.5f, -283.6f};
    m_Transform.scale = {0.74f, 0.74f};
}

void Player::Update(const std::shared_ptr<Map>& map) {
    HandleMovement(map);
    UpdateAnimation();
}

void Player::HandleMovement(const std::shared_ptr<Map>& map) {
    float step = 56.7f;
    int nextX = m_CurrentGridX;
    int nextY = m_CurrentGridY;
    float deltaX = 0.0f;
    float deltaY = 0.0f;

    if (m_MoveCooldown > 0) {
        m_MoveCooldown--;
        return;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        m_Direction = 2;
        nextY--; deltaY = step;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        m_Direction = 1;
        nextY++; deltaY = -step;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        m_Direction = 3;
        nextX--; deltaX = -step;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        m_Direction = 4;
        nextX++; deltaX = step;
    } else {
        m_IsMoving = false;
        return;
    }
    std::vector<std::vector<int>> levelData = map->GetLevelData();
    std::vector<std::shared_ptr<Block>> blocks = map->GetBlocks();

    if (levelData.empty() || nextY < 0 || nextY >= 11 || nextX < 0 || nextX >= 11) {
        m_IsMoving = false;
        return;
    }

    int targetID = levelData[nextY][nextX];
    if (targetID >= Config::ID::WALL_BEGIN && targetID <= Config::ID::WALL_END) {
        m_IsMoving = false;
        return;
    }

    if (targetID >= Config::ID::DOOR_BEGIN && targetID <= Config::ID::DOOR_END) {
        for (auto block : blocks) {
            if (nextX == block->GetPosition()[0] && nextY == block->GetPosition()[1]) {
                auto doorPtr = std::dynamic_pointer_cast<Door>(block);
                if (doorPtr) {
                    if (doorPtr->IsFullyOpen()) { }
                    else if (!doorPtr->IsOpen()) {
                        if (doorPtr->CanOpen({m_Inventory.yellowKey, m_Inventory.blueKey, m_Inventory.redKey})) {
                            switch (doorPtr->GetID()) {
                                case Config::ID::DOOR_YELLOW: m_Inventory.yellowKey--; break;
                                case Config::ID::DOOR_BLUE:   m_Inventory.blueKey--; break;
                                case Config::ID::DOOR_RED:    m_Inventory.redKey--; break;
                            }
                            m_IsMoving = false;
                            return;
                        }
                        else{
                            m_IsMoving = false;
                            return;
                        }
                    }
                    else {
                        m_IsMoving = false;
                        return;
                    }
                }
            }
        }
    }
    if (targetID >= Config::ID::STAIRS_BEGIN && targetID <= Config::ID::STAIRS_END) {
        if (targetID == Config::ID::STAIRS_UP) {
            m_IsMoving = false;
            m_FloorChangeRequest = 1;
            return;
        }
        if (targetID == Config::ID::STAIRS_DOWN) {
            m_IsMoving = false;
            m_FloorChangeRequest = -1;
            return;
        }
    }

    // int targetID = map[nextY][nextX];
    // if (targetID >= 100) { /* 撞到怪物 */ return; }

    m_IsMoving = true;
    m_MoveCooldown = 12;

    m_CurrentGridX = nextX;
    m_CurrentGridY = nextY;
    m_Transform.translation.x += deltaX;
    m_Transform.translation.y += deltaY;
}

void Player::UpdateAnimation() {
    if (!m_IsMoving) {
        SetImageFrame(0);
        return;
    }

    unsigned int currentTime = SDL_GetTicks();

    if (currentTime - m_LastFrameTime > 150) {
        m_CurrentFrame = (m_CurrentFrame + 1) % 4;
        SetImageFrame(m_CurrentFrame);
        m_LastFrameTime = currentTime;
    }
}

void Player::SetImageFrame(int index) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    if (temp) {
        temp->SetImage(RESOURCE_DIR "/Image/Player/player_"+std::to_string(m_Direction)+std::to_string(index+1)+".BMP");
    }
}

void Player::SetPosition(int x, int y) {
    m_CurrentGridX = x;
    m_CurrentGridY = y;
    m_Direction = 1;
    SetImageFrame(0);

    m_IsMoving = false;
    m_MoveCooldown = 15;

    float step = 56.7f;
    float startX = -141.5f;
    float startY = 283.6f;

    m_Transform.translation.x = startX + (x * step);
    m_Transform.translation.y = startY - (y * step);
}

