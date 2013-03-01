#include "PlayersManager.h"

PlayersManager::PlayersManager() :
    m_players(),
    m_currentId(0),
    m_emptyPlayer(new Player("", rageLib::sdl::Colors::get()->white))
{
}

PlayersManager::~PlayersManager()
{
    for(auto player : m_players) delete player;
}

PlayersManager* PlayersManager::create(std::string name, uint32_t color) {
    if(color == 0) return this;
    Player* player = new Player(name, color);

    if(std::find(m_players.cbegin(), m_players.cend(), player) != m_players.cend()) {
        delete player;
        return this;
    }

    m_players.push_back(player);
    return this;
}

Player* PlayersManager::currentPlayer() const {
    return m_players[m_currentId];
}

int PlayersManager::currentId() const {
    return m_currentId;
}

void PlayersManager::next() {
    if(this->count() <= 0) return;
    if(++ m_currentId >= this->count()) m_currentId = 0;
}

void PlayersManager::prev() {
    if(this->count() <= 0) return;
    if(-- m_currentId < 0) m_currentId = this->count() - 1;
}

int PlayersManager::count() const {
    return m_players.size();
}

std::vector<Player*> const& PlayersManager::getList() const {
    return m_players;
}

int PlayersManager::getScoreSum() const {
    int score;
    for(auto player : m_players) score += player->getScore();
    return score;
}

Player const* PlayersManager::getEmptyPlayer() const {
    return m_emptyPlayer;
}

Player const* PlayersManager::getWinner() const {
    if(this->count() == 0) return m_emptyPlayer;
    Player* winner = m_players[0];
    for(auto player : m_players) {
        if(player->getScore() >= winner->getScore()) winner = player;
    }

    return winner;
}

void PlayersManager::eraseScores() {
    for(auto player : m_players) {
        player->eraseScore();
    }
}
