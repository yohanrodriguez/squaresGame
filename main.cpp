/*!
*   \file main.cpp
*   \brief Main
*   \author A. Kryzaal
*   \version 0.1
*   \date 04/01/2012
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>

#include "src/Grid.h"
#include "src/Player.h"
#include "src/PlayersManager.h"

/*!
*   \brief Indique quand sortir du jeu
*/
bool continueGame = true;

/*!
*   \brief Initialise la SDL
*/
void startSDL();

int main (void) {
    int nbPlayers;
    int grid_size;

    std::cout << "Bienvenue dans squaresGame Beta 1" << std::endl;

    std::cout << "Entrez le nombre de joueurs ( 2 - 8 )" << std::endl;
    std::cin >> nbPlayers;
    while(nbPlayers < 2 || nbPlayers > 8)
    {
        std::cout << std::endl << "Mauvaise valeur" << std::endl;
        std::cout << "Entrez le nombre de joueurs ( 2 - 8 )" << std::endl;
        std::cin >> nbPlayers;
    }

    std::cout << std::endl << "Entrez la taille de la grille ( 5 - 30 )" << std::endl;
    std::cin >> grid_size;
    while (grid_size < 5 || grid_size > 30)
    {
        std::cout << std::endl << "Mauvaise valeur" << std::endl;
        std::cout << std::endl << "Entrez la taille de la grille ( 5 - 30 )" << std::endl;
        std::cin >> grid_size;
    }

    std::vector<std::string> players;

    for(int i = 0; i != nbPlayers; ++i)
    {
        std::cout << std::endl << "Entrez le nom du joueur " << i+1 << std::endl;
        std::string playerName;
        std::cin >> playerName;

        players.push_back(std::string(playerName));
    }

    startSDL();

    std::vector<uint32_t> colors = {
        rageLib::sdl::Colors::get()->blue,
        rageLib::sdl::Colors::get()->red,
        rageLib::sdl::Colors::get()->green,
        rageLib::sdl::Colors::get()->yellow,
        rageLib::sdl::Colors::get()->magenta,
        rageLib::sdl::Colors::get()->cyan,
        rageLib::sdl::Colors::get()->lightblue,
        rageLib::sdl::Colors::get()->lightred
    };

    int i=0;
    for(auto player : players) PlayersManager::singleton()->create(player, colors[i++]);

    /*
    *   BLACKBOX : Separateur d'images
    */
    SDL_Rect blackrect = {0, 0, 1024, 768};
    SDL_Surface* const blackbox = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_HWSURFACE, 1024, 768, 32, 0, 0, 0, 0);
    SDL_FillRect(blackbox, &blackrect, SDL_MapRGB(blackbox->format, 255, 255, 255));

    Grid myGrid(grid_size, grid_size);

    /**
    * Boucle affichage
    */
    float const fps = 30.00000000;
    float const frametime = 1000.00000000/fps;
    Uint64 previousTick = SDL_GetTicks();

    while(continueGame) {
        SDL_BlitSurface(blackbox, NULL, SDL_GetVideoSurface(), NULL);

        rageLib::EventCatcher::get()->poll();
        myGrid.blit();
        SDL_Flip(SDL_GetVideoSurface());

        if(SDL_GetTicks() - previousTick < frametime)
            SDL_Delay(frametime - (SDL_GetTicks() - previousTick));
        previousTick = SDL_GetTicks();
    }

    PlayersManager::kill();

    SDL_Quit();
    return 0;
}

void startSDL() {
    if(-1 == SDL_Init(SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);

    if(NULL == SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) {
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("squaresGame", NULL);
    TTF_Init();
}
