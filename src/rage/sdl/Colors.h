#ifndef rageLib_sdl_Colors_H
#define rageLib_sdl_Colors_H

/*!
*   \file Colors.h
*   \brief Liste statique de couleurs
*   \author A. Kryzaal
*   \version 0.1
*   \date 03/01/2012
*   \todo Passer en dynamique style AEBECE comme ce qu'il se fait en CSS
*/

#include <SDL/SDL.h>

/*!
*   \namespace rageLib
*   \brief Ensemble de classes appartenant a la bibliothéque Rage Solutions C++
*/
namespace rageLib{

/*!
*   \namespace rageLib::sdl
*   \brief Sous-ensemble de rageLib contenant des outils pour la SDL
*/
namespace sdl{

/*!
*   \class Colors Colors.h
*   \brief Simple liste de couleurs en Singleton statique
*/
class Colors {

public:
    /*!
    *   \brief Méthode Singleton
    */
    static Colors* get() {
        static Colors* instance(nullptr);
        if(nullptr == instance) {
            instance = new Colors();
        }
        return instance;
    }

    //! \brief Blanc
    uint32_t const white;
    //! \brief Rouge
    uint32_t const red;
    //! \brief Rouge clair loupé
    uint32_t const lightred;
    //! \brief Vert
    uint32_t const green;
    //! \brief Bleu
    uint32_t const blue;
    //! \brief Bleu clair raté
    uint32_t const lightblue;
    //! \brief Noir
    uint32_t const black;
    //! \brief Magenta
    uint32_t const magenta;
    //! \brief Cyan
    uint32_t const cyan;
    //! \brief Jaune
    uint32_t const yellow;
    //! \brief Gris foncé
    uint32_t const gray;
    //! \brief Gris clair
    uint32_t const grey;

private:

    /*!
    *   \brief Constructeur de Colors
    */
    Colors() :
        white(SDL_MapRGB(     SDL_GetVideoSurface()->format, 255, 255, 255)),
        red(SDL_MapRGB(       SDL_GetVideoSurface()->format, 255, 0, 0)),
        lightred(SDL_MapRGB(      SDL_GetVideoSurface()->format, 128, 32, 32)),
        green(SDL_MapRGB(     SDL_GetVideoSurface()->format, 0, 255, 0)),
        blue(SDL_MapRGB(      SDL_GetVideoSurface()->format, 0, 0, 255)),
        lightblue(SDL_MapRGB(      SDL_GetVideoSurface()->format, 32, 32, 128)),
        black(SDL_MapRGB(     SDL_GetVideoSurface()->format, 0, 0, 0)),
        magenta(SDL_MapRGB(   SDL_GetVideoSurface()->format, 255, 0, 255)),
        cyan(SDL_MapRGB(      SDL_GetVideoSurface()->format, 0, 255, 255)),
        yellow(SDL_MapRGB(    SDL_GetVideoSurface()->format, 255, 255, 0)),
        gray(SDL_MapRGB(      SDL_GetVideoSurface()->format, 128, 128, 128)),
        grey(SDL_MapRGB(      SDL_GetVideoSurface()->format, 200, 200, 200)) {
    }

};
}
}

#endif // rageLib_sdl_Colors_H
