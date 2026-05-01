#include "Player.hpp"
#include "Util/Time.hpp"
#include "GameConstants.hpp"
#include "Block/Door.hpp"
#include "Block/Props.hpp"

Player::Player() : Character(RESOURCE_DIR "/Image/Player/player_11.BMP", 50.0f) {
    m_Direction = 1;
    m_CurrentGridX = 5;
    m_CurrentGridY = 10;
    m_Transform.translation = {Config::MAP_OFFSET_X + (m_CurrentGridX * Config::TILE_SIZE), Config::MAP_OFFSET_Y - (m_CurrentGridY * Config::TILE_SIZE)};
    m_Transform.scale = {0.74f, 0.74f};
}

int PlayerStats::CalculateDamage(EnemyStats enemyStats) const {
    int Dnorm = std::max(0, atk - enemyStats.def);
    if (Dnorm <= 0) {
        return 999999;
    }
    float critRate = std::min(1.0f, level * 0.005f);       // 暴擊率
    float Davg = Dnorm * (1.0f + critRate);                             // 總攻
    int Tavg = static_cast<int>(std::ceil(enemyStats.hp / Davg));     // 回合數

    int Dm = std::max(0, enemyStats.atk - def);            // 怪打玩家基礎傷害
    int totalLoss = (Tavg - 1) * Dm;                                    // 戰鬥總扣血
    int specialLoss = 0;
    if (enemyStats.loss > 0 && enemyStats.loss < 1) {
        specialLoss = static_cast<int>(enemyStats.loss * hp);   // 百分比扣血
    }
    else if (enemyStats.loss >= 1) {
        specialLoss = static_cast<int>(enemyStats.loss);                // 固定值扣血
    }

    return totalLoss + specialLoss;
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

void Player::SetStats(PlayerLabel::Stat type, int value) {
    switch (type) {
        case PlayerLabel::Stat::LEVEL: m_Stats.level = value; break;
        case PlayerLabel::Stat::HP: m_Stats.hp = value; break;
        case PlayerLabel::Stat::ATK: m_Stats.atk = value; break;
        case PlayerLabel::Stat::DEF: m_Stats.def = value; break;
        case PlayerLabel::Stat::GOLD: m_Stats.gold = value; break;
        case PlayerLabel::Stat::EXP: m_Stats.exp = value; break;
    }
}

void Player::SetKey(PlayerLabel::Key type, int value) {
    switch (type) {
        case PlayerLabel::Key::YELLOW: m_Inventory.yellowKey = value; break;
        case PlayerLabel::Key::BLUE: m_Inventory.blueKey = value; break;
        case PlayerLabel::Key::RED: m_Inventory.redKey = value; break;
    }
}

void Player::SetItem(PlayerLabel::Item type, bool value) {
    switch (type) {
        case PlayerLabel::Item::HOLYCROSS: m_Inventory.hasholyCross = value; break;
        case PlayerLabel::Item::REDVERI: m_Inventory.hasredveri = value; break;
        case PlayerLabel::Item::BLUEVERI: m_Inventory.hasblueveri = value; break;
        case PlayerLabel::Item::GREENVERI: m_Inventory.hasgreenveri = value; break;
        case PlayerLabel::Item::GEMHOE: m_Inventory.hasgemhoe = value; break;
        case PlayerLabel::Item::GODKNIFESIGN: m_Inventory.hasgodknifesign = value; break;
        case PlayerLabel::Item::WINDCOMPASS: m_Inventory.haswindCompass = value; break;
    }
}

void Player::AddStats(PlayerLabel::Stat type, int value) {
    switch (type) {
        case PlayerLabel::Stat::LEVEL: m_Stats.level += value; break;
        case PlayerLabel::Stat::HP: m_Stats.hp += value; break;
        case PlayerLabel::Stat::ATK: m_Stats.atk += value; break;
        case PlayerLabel::Stat::DEF: m_Stats.def += value; break;
        case PlayerLabel::Stat::GOLD: m_Stats.gold += value; break;
        case PlayerLabel::Stat::EXP: m_Stats.exp += value; break;
    }
}

void Player::AddKey(PlayerLabel::Key type, int value) {
    switch (type) {
        case PlayerLabel::Key::YELLOW: m_Inventory.yellowKey += value; break;
        case PlayerLabel::Key::BLUE: m_Inventory.blueKey += value; break;
        case PlayerLabel::Key::RED: m_Inventory.redKey += value; break;
    }
}
