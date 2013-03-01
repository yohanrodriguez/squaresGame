#ifndef squaresGame_Player_H
#define squaresGame_Player_H

/*!
*   \file Player.h
*   \brief Code des joueurs dans le jeu des carrés
*   \author E. Sandre
*   \version 0.2
*   \date 01/03/2013
*/

#include <string>
#include "rage/sdl/Colors.h"

/*!
*   \class Player Player.h
*   \brief Représente un joueur dans le jeu des carrés
*/
class Player {

public:
    /*!
    *   \brief Constructeur de Player
    *   \param name : le nom du joueur
    */
    Player(std::string const name, uint32_t color);

    /*!
    *   \brief Opérateur ==, version références
    */
    bool operator==(Player const& p2) const;

    /*!
    *   \brief Opérateur ==, version pointeurs
    */
    bool operator==(Player const* p2) const;

    /*!
    *   \brief Accesseur lecture pour le nom
    *   \return Le nom du joueur
    */
    std::string const& getName() const;

    /*!
    *   \brief Ajoute un point au joueur
    */
    void addPoint() const;

    /*!
    *   \brief Accesseur lecture pour le score
    *   \return Le score du joueur
    */
    unsigned int getScore() const;

    /*!
    *   \brief Efface le score
    */
    void eraseScore() const;

    /*!
    *   \brief Accesseur lecture pour la couleur
    *   \return La couleur correspondant au joueur
    */
    uint32_t getColor() const;

private:

    /*!
    *   \brief Le nom du joueur
    */
    std::string const m_name;

    /*!
    *   \brief La couleur rattachée au joueur
    */
    uint32_t const m_color;

    /*!
    *   \brief Le score du joueur
    */
    mutable unsigned int m_score;

    Player();
    Player(Player const& origin);
    Player(Player const* origin);
    Player const& operator=(Player const& origin);
    Player const* operator=(Player const* origin);
};

#endif // squaresGame_Player_H
