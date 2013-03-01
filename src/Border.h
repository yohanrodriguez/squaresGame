#ifndef squaresGame_Border_H
#define squaresGame_Border_H

/*!
*   \file Border.h
*   \brief Code des bordures des cases de la grille
*   \author E. Sandre
*   \version 0.2
*   \date 01/03/2013
*/

#include <ctime>
#include "Player.h"
#include "PlayersManager.h"

/*!
*   \class Border Border.h
*   \brief Représente une bordure entre 2 cases ou entre une case et le bord
*/
class Border {
public:

    /*!
    *   \brief Constructeur par défaut de Border
    */
    Border();

    /*!
    *   \brief Accesseur lecture du claimTime
    *   \return Le nombre de ticks a l'appropriation de la bordure
    */
    clock_t getClaimTime() const;

    /*!
    *   \brief Accesseur lecture pour le propriétaire
    *   \return Le joueur propriétaire de la bordure
    */
    Player const* getOwner() const;

    /*!
    *   \brief Renvoie un booléen indiquant si la case a un propriétaire ou non
    */
    bool hasOwner() const;

    /*!
    *   \brief Accesseur écriture pour le propriétaire
    *   \param owner : Le nouveau propriétaire, peut être nul
    */
    void setOwner(Player const* owner);

protected:

    /*!
    *   \brief Le propriétaire de la bordure
    *   Peut être nul
    */
    Player const* m_owner;

    /*!
    *   \brief Le moment de changement de propriétaire
    */
    clock_t m_claimTime;

private:
    Border(Border const& origin);
    Border(Border const* origin);
    Border const& operator=(Border const& origin);
    Border const* operator=(Border const* origin);
};

#endif // squaresGame_Border_H
