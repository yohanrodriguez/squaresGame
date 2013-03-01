#ifndef squaresGame_Grid_H
#define squaresGame_Grid_H

/*!
*   \file Grid.h
*   \brief La grille du jeu et les traitements reliés
*   \author A. Kryzaal
*   \version 0.1
*   \date 03/01/2012
*/

#include <vector>
#include <SDL/SDL_ttf.h>

#include "rage/event/EventReceiver.h"
#include "rage/sdl/Colors.h"

#include "Case.h"
#include "PlayersManager.h"
#include "PlayerManagerView.h"

/*!
*   \class Grid Grid.h
*   \brief La grille du jeu et ses traitements
*/
class Grid : public rageLib::EventReceiver {

public:
    /*!
    *   \brief Constructeur d'une grille
    *   \param x : le nombre de cases en largeur
    *   \param y : le nombre de cases en hauteur
    */
    Grid(uint8_t x = 10, uint8_t y = 10);

    /*!
    *   \brief Destructeur de Grid
    */
    ~Grid();

    /*!
    *   \brief Affiche la grille a l'écran
    *   \todo Passer un pointeur de surface ou coller plutot que d'imposer l'ecran
    */
    void blit() const;

protected:

    /*!
    *   \struct squaresGame::Grid::margins
    *   \brief Les marges d'une grille
    *   \todo Passer en paramétrable
    */
    static struct margins{

        /*!
        *   \brief Marge du haut
        */
        static uint8_t const top = 25;

        /*!
        *   \brief Marge du bas
        */
        static uint8_t const bottom = 15;

        /*!
        *   \brief Marge de gauche
        */
        static uint8_t const left = 25;

        /*!
        *   \brief Marge de droite
        */
        static uint8_t const right = 15;
    } const mrgins;

    /*!
    *   \struct squaresGame::Grid::borders
    *   \brief Les bordures d'une grille
    */
    struct borders {
        /*!
        *   \brief Sous-Constructeur de Grid::borders
        *   \param x : Le nombre de cases en largeur de la grille
        *   \param y : Le nombre de cases en hauteur de la grille
        */
        borders(uint8_t x, uint8_t y);

        /*!
        *   \struct squaresGame::Grid::borders::horborder
        *   \brief Les bordures horizontales
        */
        struct horborder{

            /*!
            *   \brief Sous-Constructeur de Grid::borders::horborder
            *   \param x : Le nombre de cases en largeur de la grille
            *   \param y : Le nombre de cases en hauteur de la grille
            *   \param w: La largeur d'une case
            */
            horborder(uint8_t x, uint8_t y, uint8_t w);

            /*!
            *   \brief Le tableau contenant les adresses vers toutes les bordures horizontales
            */
            mutable std::vector<std::vector<std::pair<Border*,bool>>> data;

            /*!
            *   \brief Le rect d'un bordure horizontale
            */
            SDL_Rect const rect;

            /*!
            *   \brief La surface d'une bordure horizontale
            */
            SDL_Surface* const surface;

            private:
                horborder(horborder const& src);
                horborder operator=(horborder const& src);
        }
        /*!
        *   \brief Les bordures horizontales de la grille
        */
        const hor;

        /*!
        *   \struct squaresGame::Grid::borders::vertborder
        *   \brief Les bordures verticales
        */
        struct vertborder{
            /*!
            *   \brief Sous-Constructeur de Grid::borders::vertborder
            *   \param x : Le nombre de cases en largeur de la grille
            *   \param y : Le nombre de cases en hauteur de la grille
            *   \param h: La hauteur d'une case
            */
            vertborder(uint8_t x, uint8_t y, uint8_t h);

            /*!
            *   \brief Le tableau contenant les adresses vers toutes les bordures verticales
            */
            mutable std::vector<std::vector<std::pair<Border*,bool>>> data;

            /*!
            *   \brief Le rect d'un bordure verticale
            */
            SDL_Rect const rect;

            /*!
            *   \brief La surface d'une bordure verticale
            */
            SDL_Surface* const surface;

            private:
                vertborder(vertborder const& src);
                vertborder operator=(vertborder const& src);
        }
        /*!
        *   \brief Les bordures verticales de la grille
        */
        const vert;
    }
    /*!
    *   \brief Les bordures de la grille
    */
    const m_borders;

    /*!
    *   \struct squaresGame::Grid::cells
    *   \brief Les cases d'une grille
    */
    struct cells{
        /*!
        *   \brief Sous-Constructeur de Grid::cells
        *   \param x : Le nombre de cases en largeur de la grille
        *   \param y : Le nombre de cases en hauteur de la grille
        *   \param bordrs : Les bordures de la grille
        */
        cells(uint8_t x, uint8_t y, borders const& bordrs);

        /*!
        *   \brief Le tableau contenant les adresses vers toutes les cases
        */
        std::vector<std::vector<Case*>> data;

        /*!
        *   \brief La surface d'une case
        */
        SDL_Rect const rect;

        /*!
        *   \brief La surface d'une case
        */
        SDL_Surface* const surface;

        private:
            cells(cells const& src);
            cells operator=(cells const& src);
    }
    /*!
    *   \brief Les cases de la grille
    */
    const m_cells;

    /*!
    *   \struct squaresGame::Grid::grid
    *   \brief Les infos basiques d'une grille
    */
    struct grid {
        /*!
        *   \brief Sous-Constructeur de Grid::grid
        *   \param x : Le nombre de cases en largeur de la grille
        *   \param y : Le nombre de cases en hauteur de la grille
        *   \param cell_w : La largeur d'une case de la grille
        *   \param cell_h : La hauteur d'une case de la grille
        */
        grid(uint8_t const x, uint8_t const y, uint16_t cell_w, uint16_t cell_h);

        /*!
        *   \brief Le nombre de cases en largeur de la grille
        */
        uint8_t const x:6;

        /*!
        *   \brief Le nombre de cases en hauteur de la grille
        */
        uint8_t const y:6;

        /*!
        *   \brief Le rect de la grille
        */
        SDL_Rect const rect;

        /*!
        *   \brief La surface de la grille
        */
        SDL_Surface* const surface;

    }
    /*!
    *   \brief Les infos de la grille elle-meme
    */
    const m_grid;

    /*!
    *   \struct squaresGame::Grid::interface
    *   \brief L'interface avec les infos du jeu
    */
    struct interface {
        /*!
        *   \brief Sous-Constructeur de Grid::interface
        *   \param grid_w : La largeur de la grille
        *   \param grid_h : La hauteur de la grille
        */
        interface(uint16_t grid_w, uint16_t grid_h);

        /*!
        *   \brief La surface de l'interface
        */
        SDL_Surface* const surface;

        /*!
        *   \brief Le rect de l'interface
        */
        SDL_Rect const rect;
    }
    /*!
    *   \brief L'interface pour la partie en cours dans la grille
    */
    const m_interface;

    /*!
    *   \brief Indique si la partie est terminée ou non
    */
    bool m_gameIsEnd;

private:

    /*!
    *   \brief Colle les cases sur une surface
    *   \param dest : la surface de destination
    */
    void blitCases(SDL_Surface* const dest) const;

    /*!
    *   \brief Colle les bordures sur une surface
    *   \param dest : la surface de destination
    */
    void blitBorders(SDL_Surface* const dest) const;

    /*!
    *   \brief Colle l'interface sur une surface
    *   \param dest : la surface de destination
    */
    void blitInterface(SDL_Surface* const dest) const;

    /*!
    *   \brief Colle l'ecran de fin de partie sur une surface
    *   \param dest : la surface de destination
    */
    void blitGameOver(SDL_Surface* const dest) const;

    void onMouseUp(SDL_MouseButtonEvent const event);
    void onMouseMotion(SDL_MouseMotionEvent const event);
    void onQuit();

    /*!
    *   \brief Recalcule les scores
    */
    void processScores();

    /*!
    *   \brief Clot la partie
    */
    void endGame();

    Grid(Grid const& src);
    Grid operator=(Grid const& src);
};

#endif // squaresGame_Grid_H
