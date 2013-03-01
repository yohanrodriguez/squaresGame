#ifndef PLAYERMANAGERVIEW_H
#define PLAYERMANAGERVIEW_H

/*!
*   \file PlayerManagerView.h
*   \brief Vue SDL pour le PlayerManager
*   \author E. Sandre
*   \version 0.2
*   \date 01/03/2013
*/

#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include "PlayersManager.h"
#include "rage/FontManager.h"

/*!
*   \class PlayerManagerView PlayerManagerView.h
*   \brief Représente un joueur dans le jeu des carrés
*/
class PlayerManagerView
{
    public:

        /*!
        *   \brief Blitte l'interface sur dst
        *   \param dst : surface de destination
        */
        void blit(SDL_Surface* dst);
};

#endif // PLAYERMANAGERVIEW_H
