#include "Player.h"

Player::Player(std::string const name, uint32_t color):
    m_name(name),
    m_color(color),
    m_score(0)
{
}

/*!
*   Compare simplement le nom des deux joueurs et leur couleur pour rendre le verdict
*/
bool Player::operator==(Player const& p2) const {
    return this->getName() == p2.getName() && this->getColor() == p2.getColor() ? true : false;
}

/*!
*   Compare simplement le nom des deux joueurs et leur couleur pour rendre le verdict
*/
bool Player::operator==(Player const* p2) const {
    return this->getName() == p2->getName() && this->getColor() == p2->getColor() ? true : false;
}

std::string const& Player::getName() const {
    return m_name;
}

uint32_t Player::getColor() const {
    return m_color;
}

void Player::addPoint() const {
    m_score ++;
}

unsigned int Player::getScore() const {
    return m_score;
}

void Player::eraseScore() const {
    m_score = 0;
}
