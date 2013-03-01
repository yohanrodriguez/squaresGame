#ifndef PLAYERSMANAGER_H
#define PLAYERSMANAGER_H

/*!
*   \file PlayersManager.h
*   \brief Gestionnaire de la liste des joueurs
*   \author E. Sandre
*   \version 0.2
*   \date 01/03/2013
*/

#include <string>
#include <vector>
#include <algorithm>

#include "rage/Singleton.h"
#include "Player.h"

class PlayersManager : public Singleton<PlayersManager>
{
    friend class Singleton<PlayersManager>;
    public:
        PlayersManager* create(std::string name, uint32_t color);

        Player* currentPlayer() const;
        int currentId() const;

        void next();
        void prev();
        int count() const;

        std::vector<Player*> const& getList() const;
        int getScoreSum() const;

        Player const* getWinner() const;
        Player const* getEmptyPlayer() const;
        void eraseScores();
    private:
        std::vector<Player*> m_players;
        int m_currentId = 0;
        Player const* m_emptyPlayer;

        PlayersManager();
        virtual ~PlayersManager();

        PlayersManager(PlayersManager const& orig);
        PlayersManager(PlayersManager* orig);
        void operator=(PlayersManager const& orig);
        void operator=(PlayersManager* orig);

};

#endif // PLAYERSMANAGER_H
