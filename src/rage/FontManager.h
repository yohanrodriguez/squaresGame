#ifndef FONTMANAGER_H
#define FONTMANAGER_H

/*!
*   \file FontManager.h
*   \brief Gestionnaire de polices
*   \author E. Sandre
*   \version 0.1
*   \date 01/03/2013
*/

#include <map>
#include <string>
#include <SDL/SDL_ttf.h>
#include "Singleton.h"

/*!
*   \class FontManager FontManager.h
*   \brief Gére une liste de polices en Singleton
*/
class FontManager : public Singleton<FontManager>, public std::map<std::string, TTF_Font*>
{
    friend class Singleton<FontManager>;
    FontManager();
    virtual ~FontManager() {};
};

#endif // FONTMANAGER_H
