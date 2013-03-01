#ifndef squaresGame_Case_H
#define squaresGame_Case_H

/*!
*   \file Case.h
*   \brief Code des cases de la grille
*   \author E. Sandre
*   \version 0.2
*   \date 01/03/2013
*/

#include "Border.h"

/*!
*   \class Case Case.h
*   \brief Représente une case dans la grille de jeu
*/
class Case {

public:
    /*!
    *   \brief Constructeur d'une case, il faut indiquer les adresses des 4 bordures
    *   \param top : L'adresse de la bordure du haut
    *   \param bottom : L'adresse de la bordure du bas
    *   \param left: L'adresse de la bordure de gauche
    *   \param right : L'adresse de la bordure de droite
    */
    Case(Border* const top, Border* const bottom, Border* const left, Border* const right);

    /*!
    *   \brief Accesseur lecture pour le propriétaire
    *   \return Le joueur propriétaire de la case
    */
    Player const* getOwner() const;

    /*!
    *   \brief Accesseur lecture pour la bordure du haut
    *   \return L'adresse de la bordure
    */
    Border* getTopBorder() const;

    /*!
    *   \brief Accesseur lecture pour la bordure de gauche
    *   \return L'adresse de la bordure
    */
    Border* getLeftBorder() const;

    /*!
    *   \brief Accesseur lecture pour la bordure de droite
    *   \return L'adresse de la bordure
    */
    Border* getRightBorder() const;

    /*!
    *   \brief Accesseur lecture pour la bordure du bas
    *   \return L'adresse de la bordure
    */
    Border* getBottomBorder() const;

private:

    /*!
    *   \struct Case::caseBorders
    *   \brief Les 4 bordures d'une case
    */
    struct caseBorders{
        /*!
        *   \brief Bordure du haut ( x, y )
        */
        Border* const top;

        /*!
        *   \brief Bordure du bas ( x, y+1 )
        */
        Border* const bottom;

        /*!
        *   \brief Bordure de gauche ( x, y )
        */
        Border* const left;

        /*!
        *   \brief Bordure du droit ( x+1, y )
        */
        Border* const right;
    }
    /*!
    *   \brief Les 4 bordures de la case
    */
    const m_borders;

    Case(Case const& origin);
    Case operator=(Case const& src);
};

#endif // squaresGame_Case_H
