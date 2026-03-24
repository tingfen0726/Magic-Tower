#include "Player.hpp"
#include "Util/Time.hpp"
#include "GameConstants.hpp"
#include "PlayerConstants.hpp"
#include "Block/Door.hpp"
#include "Block/Props.hpp"


//const float TILE_SIZE = 56.7f;
// const float MAP_OFFSET_X = -141.5f;
// const float MAP_OFFSET_Y = 283.6f;

Player::Player() : Character(RESOURCE_DIR "/Image/Player/player_11.BMP", 50.0f) {
    m_Direction = 1;
    m_CurrentGridX = 5;
    m_CurrentGridY = 10;
    m_Transform.translation = {Config::MAP_OFFSET_X + (m_CurrentGridX * Config::TILE_SIZE), Config::MAP_OFFSET_Y - (m_CurrentGridY * Config::TILE_SIZE)};
    m_Transform.scale = {0.74f, 0.74f};
}

void Player::Update() {
    UpdateAnimation();
}

void Player::GetNextGrid(int &outX, int &outY, int &outDir) {
    outX = m_CurrentGridX;
    outY = m_CurrentGridY;
    outDir = m_Direction;
    if (m_MoveCooldown > 0) {
        m_MoveCooldown--;
        return;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::W)) { outDir = 2; outY--;}
    else if (Util::Input::IsKeyPressed(Util::Keycode::S)) { outDir = 1; outY++;}
    else if (Util::Input::IsKeyPressed(Util::Keycode::A)) { outDir = 3; outX--;}
    else if (Util::Input::IsKeyPressed(Util::Keycode::D)) { outDir = 4; outX++;}
    else { m_IsMoving = false;}

}
void Player::MoveToGrid(int nextX, int nextY, int dir) {
    m_Direction = dir;
    m_IsMoving = true;
    m_MoveCooldown = 12;

    float step = Config::TILE_SIZE;
    float deltaX = (nextX - m_CurrentGridX) * step;
    float deltaY = -(nextY - m_CurrentGridY) * step;

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

    m_Transform.translation.x = Config::MAP_OFFSET_X + (x * Config::TILE_SIZE);
    m_Transform.translation.y = Config::MAP_OFFSET_Y - (y * Config::TILE_SIZE);
}

