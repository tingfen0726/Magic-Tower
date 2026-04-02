#include "Player.hpp"
#include "Util/Time.hpp"
#include "GameConstants.hpp"
#include "PlayerConstants.hpp"
#include "Block/Door.hpp"
#include "Block/Props.hpp"

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
void Player::StepInPlace(int dir) {
    m_Direction = dir;
    m_IsMoving = true;
    m_MoveCooldown = 8;
}
void Player::MoveToGrid(int nextX, int nextY, int dir) {
    m_Direction = dir;
    m_IsMoving = true;
    m_MoveCooldown = 8;

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

bool Player::Engage(EnemyStats enemyStats) { //
    int Dnorm = std::max(0, m_Stats.atk - enemyStats.def);      //玩攻怪
    if (Dnorm <= 0) {
        m_Stats.hp = 0;
        return false;
    }
    float critRate = std::min(1.0f, m_Stats.level * 0.005f);    //暴擊
    float Davg = Dnorm * (1.0f + critRate);                          //總攻
    int Tavg = static_cast<int>(std::ceil(enemyStats.hp / Davg));  //回合
    int Dm = std::max(0, enemyStats.atk - m_Stats.def);         //怪攻玩
    int totalLoss = (Tavg - 1) * Dm;                                 //總扣血

    if (enemyStats.loss > 0 && enemyStats.loss < 1) { m_Stats.hp -= enemyStats.loss * m_Stats.hp;}
    else if (enemyStats.loss >= 1) {m_Stats.hp -= enemyStats.loss;}

    if (m_Stats.hp > totalLoss) {
        m_Stats.hp -= totalLoss;
        m_Stats.gold += enemyStats.gold;
        m_Stats.exp += enemyStats.exp;
        return true;
    }
    else {
        m_Stats.hp = 0;
        return false;
    }
}
