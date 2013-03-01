#include "FontManager.h"

FontManager::FontManager() :
    Singleton(),
    std::map<std::string, TTF_Font*>()
{
    this->operator[]("default") = TTF_OpenFont(
                                    /* file = */    "font.ttf",
                                    /* size = */    40
                                );
}
