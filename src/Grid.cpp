#include "Grid.h"

#define BORDER_WEIGHT 4
#define HOVER_RADIUS 10
#define MAX_ROW_NB 30
#define MAX_COLUMN_NB 30
//#define DEBUG

#define CELL_W (int16_t)((SDL_GetVideoSurface()->w - Grid::mrgins.left - Grid::mrgins.right) / x)
#define CELL_H (int16_t)((SDL_GetVideoSurface()->h - Grid::mrgins.bottom - Grid::mrgins.top) / y)

extern bool continueGame;

Grid::Grid(uint8_t x, uint8_t y):
    EventReceiver   (),
    m_borders       (x, y),
    m_cells         (x, y, m_borders),
    m_grid          (x, y, m_cells.rect.w, m_cells.rect.h),
    m_interface     (m_grid.rect.w, m_grid.rect.h),
    m_gameIsEnd     (false)
{
}

Grid::~Grid() {
    SDL_FreeSurface ((SDL_Surface*)m_interface.surface);
    SDL_FreeSurface((SDL_Surface*)m_grid.surface);
    SDL_FreeSurface((SDL_Surface*)m_cells.surface);
    SDL_FreeSurface((SDL_Surface*)m_borders.hor.surface);
    SDL_FreeSurface((SDL_Surface*)m_borders.vert.surface);

    for(auto row : m_cells.data) {
        for(auto cell : row) {
            delete cell;
        }
    }

    for(auto row : m_borders.hor.data) {
        for(auto border : row) {
            delete border.first;
        }
    }

    for(auto row : m_borders.vert.data) {
        for(auto border : row) {
            delete border.first;
        }
    }
}

Grid::grid::grid(uint8_t xx, uint8_t yy, uint16_t cell_w, uint16_t cell_h):
    x           (xx),
    y           (yy),
    rect        ({
                    /* x = */   Grid::mrgins.left,
                    /* y = */   Grid::mrgins.top,
                    /* w = */   (int16_t)((cell_w * x) + BORDER_WEIGHT),
                    /* h = */   (int16_t)((cell_h * y) + BORDER_WEIGHT)
                }),
    surface     (SDL_CreateRGBSurface(
                    /* flags = */   SDL_SRCALPHA | SDL_HWSURFACE,
                    /* w = */       rect.w,
                    /* h = */       rect.h,
                    32, 0, 0, 0, 0
                ))
{
}

Grid::borders::borders(uint8_t x, uint8_t y):
    hor     (x, y, CELL_W),
    vert    (x, y, CELL_H)
{}

Grid::borders::horborder::horborder(uint8_t x, uint8_t y, uint8_t w):
    data        (),
    rect        ({
                    /* x = */   0,
                    /* y = */   0,
                    /* w = */   w,
                    /* h = */   BORDER_WEIGHT
                }),
    surface     (SDL_CreateRGBSurface(
                    /* flags = */   SDL_SRCALPHA | SDL_HWSURFACE,
                    /* w = */       w,
                    /* h = */       BORDER_WEIGHT,
                    32, 0, 0, 0, 0
                ))
{
    for(uint8_t row_id = 0; row_id <= y; ++row_id) {
        data.push_back(std::vector<std::pair<Border*,bool>>());
        for(uint8_t column_id = 0; column_id < x; ++column_id) {
            data[row_id].push_back(std::pair<Border*,bool>(new Border, false));
        }
    }
}

Grid::borders::vertborder::vertborder(uint8_t x, uint8_t y, uint8_t h):
    data        (),
    rect        ({
                    /* x = */   0,
                    /* y = */   0,
                    /* w = */   BORDER_WEIGHT,
                    /* h = */   h
                }),
    surface     (SDL_CreateRGBSurface(
                    /* flags = */   SDL_SRCALPHA | SDL_HWSURFACE,
                    /* w = */       BORDER_WEIGHT,
                    /* h = */       h,
                    32, 0, 0, 0, 0
                ))
{
    for(uint8_t row_id = 0; row_id < y; ++row_id) {
        data.push_back(std::vector<std::pair<Border*,bool>>());
        for(uint8_t column_id = 0; column_id <= x; ++column_id) {
            data[row_id].push_back(std::pair<Border*,bool>(new Border, false));
        }
    }
}

Grid::cells::cells(uint8_t x, uint8_t y, borders const& bordrs):
    data        (),
    rect        ({
                    /* x = */   0,
                    /* y = */   0,
                    /* w = */   (CELL_W < CELL_H) ? CELL_W : CELL_H,    //Les cases sont carrées, alors on prend le plus
                    /* h = */   (CELL_W < CELL_H) ? CELL_W : CELL_H     //petit entre la largeur et la hauteur
                 }),
    surface     (SDL_CreateRGBSurface(
                    /* flags = */   SDL_SRCALPHA | SDL_HWSURFACE,
                    /* w = */       (CELL_W < CELL_H) ? CELL_W : CELL_H,
                    /* h = */       (CELL_W < CELL_H) ? CELL_W : CELL_H,
                    32, 0, 0, 0, 0
                ))
{
    for(uint8_t row_id = 0; row_id < y; ++row_id) {
        data.push_back(std::vector<Case*>());
        for(uint8_t column_id = 0; column_id < x; ++column_id) {
            Case* newCase = new Case(
                /* top = */     bordrs.hor.data [row_id]    [column_id]     .first,
                /* bottom = */  bordrs.hor.data [row_id+1]  [column_id]     .first,
                /* left = */    bordrs.vert.data[row_id]    [column_id]     .first,
                /* right = */   bordrs.vert.data[row_id]    [column_id+1]   .first
            );
            data[row_id].push_back(newCase);
        }
    }
}

Grid::interface::interface(uint16_t grid_w, uint16_t grid_h):
    surface         (SDL_CreateRGBSurface(
                        /* flags = */   SDL_SRCALPHA | SDL_HWSURFACE,
                        /* w = */       grid_w/3,
                        /* h = */       grid_h,
                        32, 0, 0, 0, 0
                    )),
    rect            ({
                        /* x = */   (int16_t) (Grid::mrgins.left + grid_w),
                        /* y = */   Grid::mrgins.top,
                        /* w = */   (uint16_t)(grid_w/3),
                        /* h = */   grid_h
                     })
{
}

void Grid::blit() const {
    blitCases               (m_grid.surface);
    blitBorders             (m_grid.surface);
    blitInterface           (m_interface.surface);

    if(m_gameIsEnd) {
        blitGameOver        (m_grid.surface);
    }
    SDL_BlitSurface (
        /* src = */         m_interface.surface,
        /* src_rect = */    NULL,
        /* dst = */         SDL_GetVideoSurface(),
        /* dst_rect = */    (SDL_Rect*) &m_interface.rect
    );
    SDL_BlitSurface (
        /* src = */         m_grid.surface,
        /* src_rect = */    NULL,
        /* dst = */         SDL_GetVideoSurface(),
        /* dst_rect = */    (SDL_Rect*) &m_grid.rect
    );
}

void Grid::blitCases(SDL_Surface* const dest) const {
    for(uint8_t row_id = 0; row_id < m_grid.x; ++row_id) {
        for(uint8_t column_id = 0; column_id < m_grid.y; ++column_id) {
            SDL_Rect const px_rect = {
                /* x = */   (int16_t)(m_cells.rect.w * row_id),
                /* y = */   (int16_t)(m_cells.rect.h * column_id),
                /* w = */   0,
                /* h = */   0
            };
            SDL_FillRect(
                /* surface = */ m_cells.surface,
                /* rect = */    (SDL_Rect*) &m_cells.rect,
                /* color = */   m_cells.data[column_id][row_id]->getOwner()->getColor()
            );
            SDL_BlitSurface(
                /* src = */     m_cells.surface,
                /* src_rect = */NULL,
                /* dst = */     dest,
                /* dst_rect = */(SDL_Rect*) &px_rect
            );
        }
    }
}

void Grid::blitBorders(SDL_Surface* const dest) const {
    for(uint8_t i = 0; i <= m_grid.x; ++i) {
        for(uint8_t j = 0; j < m_grid.y; ++j) {
            SDL_Rect const px_rect = {(int16_t)(m_cells.rect.w * i), (int16_t)(m_cells.rect.h * j), 0, 0};

            if(m_borders.vert.data[j][i].second
            #ifndef DEBUG
            || m_borders.vert.data[j][i].first->hasOwner()
            #endif
            ) {
                SDL_FillRect(m_borders.vert.surface, (SDL_Rect*) &m_borders.vert.rect, rageLib::sdl::Colors::get()->black);
            }
            #ifdef DEBUG
            else if(m_borders.vert.data[j][i].first->hasOwner()) {
                SDL_FillRect(m_borders.vert.surface, (SDL_Rect*) &m_borders.vert.rect, m_borders.vert.data[j][i].first->getOwner()->getColor());
            }
            #endif
            else {
                SDL_FillRect(m_borders.vert.surface, (SDL_Rect*) &m_borders.vert.rect, rageLib::sdl::Colors::get()->grey);
            }
            SDL_BlitSurface(m_borders.vert.surface, NULL, dest, (SDL_Rect*) &px_rect);
        }
    }

    for(uint8_t i = 0; i < m_grid.x; ++i) {
        for(uint8_t j = 0; j <= m_grid.y; ++j) {
            SDL_Rect const px_rect = {(int16_t)(m_cells.rect.w * i), (int16_t)(m_cells.rect.h * j), 0, 0};

            if(m_borders.hor.data[j][i].second
            #ifndef DEBUG
            || m_borders.hor.data[j][i].first->hasOwner()
            #endif
            ) {
                SDL_FillRect(m_borders.hor.surface, (SDL_Rect*) &m_borders.hor.rect, rageLib::sdl::Colors::get()->black);
            }
            #ifdef DEBUG
            else if(m_borders.hor.data[j][i].first->hasOwner()) {
                SDL_FillRect(m_borders.hor.surface, (SDL_Rect*) &m_borders.hor.rect, m_borders.hor.data[j][i].first->getOwner()->getColor());
            }
            #endif
            else {
                SDL_FillRect(m_borders.hor.surface, (SDL_Rect*) &m_borders.hor.rect, rageLib::sdl::Colors::get()->grey);
            }

            SDL_BlitSurface(m_borders.hor.surface, NULL, dest, (SDL_Rect*) &px_rect);
        }
    }
}

void Grid::blitInterface(SDL_Surface* const dest) const {
    PlayerManagerView* view = new PlayerManagerView();
    view->blit(dest);
    delete view;
}

void Grid::blitGameOver(SDL_Surface* const dest) const {
        SDL_Surface* gameOverStr = TTF_RenderText_Shaded(
             (TTF_Font*) FontManager::singleton()->operator[]("default"),
             std::string(PlayersManager::singleton()->getWinner()->getName() + " wins !").c_str(),
             {0,0,0,0}, {255,255,255,0});
        SDL_Rect rect = {(int16_t)(m_grid.rect.w/2 - gameOverStr->w/2), (int16_t)(m_grid.rect.h/2 - gameOverStr->h/2), 0, 0};
        SDL_BlitSurface(gameOverStr, NULL, dest, &rect);
        SDL_FreeSurface(gameOverStr);
}

void Grid::processScores() {
    PlayersManager* manager = PlayersManager::singleton();
    int const previousScore = manager->getScoreSum();
    manager->eraseScores();

    for(uint8_t i = 0; i < m_grid.x; ++i) {
        for(uint8_t j = 0; j < m_grid.y; ++j) {
            auto owner = m_cells.data[j][i]->getOwner();
            if(owner->getColor() != 0) owner->addPoint();
        }
    }

    int const newScore = manager->getScoreSum();
    if(newScore == (m_grid.x*m_grid.y)) endGame();
    else if(newScore == previousScore) manager->next();
}

void Grid::endGame() {
    m_gameIsEnd = true;
}

/**
* PAVE CAESAR
*/
void Grid::onMouseUp(SDL_MouseButtonEvent const event) {
    PlayersManager* manager = PlayersManager::singleton();
    if(m_gameIsEnd) continueGame = false;

    uint16_t const modulo_x = (event.x - Grid::mrgins.left) % m_cells.rect.w;
    uint16_t const modulo_y = (event.y - Grid::mrgins.top) % m_cells.rect.h;

    if(event.x < m_grid.rect.x - HOVER_RADIUS/2 || event.x > m_grid.rect.x + m_grid.rect.w + HOVER_RADIUS/2 || event.y < m_grid.rect.y - HOVER_RADIUS/2 || event.y > m_grid.rect.y + m_grid.rect.h + HOVER_RADIUS/2) return;
    if ((modulo_x > m_cells.rect.w - HOVER_RADIUS) || (modulo_x < HOVER_RADIUS)) {
        uint8_t const column_id = (event.x - Grid::mrgins.left + HOVER_RADIUS + 1) / m_cells.rect.w;
        uint8_t const row_id = (modulo_y < HOVER_RADIUS || modulo_y > m_cells.rect.h - HOVER_RADIUS) ? MAX_ROW_NB+1 : (event.y- Grid::mrgins.top) / m_cells.rect.h;

        if(row_id+1 > m_grid.y || column_id > m_grid.x+1 || m_borders.vert.data[row_id][column_id].first->hasOwner()) return;

        m_borders.vert.data[row_id][column_id].first->setOwner(manager->currentPlayer());
        processScores();
    } else if ((modulo_y > m_cells.rect.h - HOVER_RADIUS) || (modulo_y < HOVER_RADIUS)) {
        uint8_t const row_id = (event.y - Grid::mrgins.top + HOVER_RADIUS + 1) / m_cells.rect.h;
        uint8_t const column_id = (modulo_x < HOVER_RADIUS || modulo_x > m_cells.rect.w - HOVER_RADIUS) ? MAX_COLUMN_NB+1 : (event.x- Grid::mrgins.left) / m_cells.rect.w;

        if(row_id > m_grid.y+1 || column_id+1 > m_grid.x || m_borders.hor.data[row_id][column_id].first->hasOwner()) return;

        m_borders.hor.data[row_id][column_id].first->setOwner(manager->currentPlayer());
        processScores();
    }
}

/**
* DEBUGGERI TE SALUTANT
*/
void Grid::onMouseMotion(SDL_MouseMotionEvent const event) {
    for(auto& vertRow : m_borders.vert.data) {
        for(auto& vertBorder : vertRow) {
            vertBorder.second = false;
        }
    }

    for(auto& horRow : m_borders.hor.data) {
        for(auto& horBorder : horRow) {
            horBorder.second = false;
        }
    }

    uint16_t const modulo_x = (event.x - Grid::mrgins.left) % m_cells.rect.w;
    uint16_t const modulo_y = (event.y - Grid::mrgins.top) % m_cells.rect.h;

    if ((modulo_x > m_cells.rect.w - HOVER_RADIUS) || (modulo_x < HOVER_RADIUS)) {
        uint8_t const column_id = (event.x - Grid::mrgins.left + HOVER_RADIUS + 1) / m_cells.rect.w;
        uint8_t const row_id = (modulo_y < HOVER_RADIUS || modulo_y > m_cells.rect.h - HOVER_RADIUS) ? MAX_ROW_NB+1 : (event.y- Grid::mrgins.top) / m_cells.rect.h;

        if(row_id+1 > m_grid.y || column_id > m_grid.x+1) return;

        m_borders.vert.data[row_id][column_id].second = true;
    } else if ((modulo_y > m_cells.rect.h - HOVER_RADIUS) || (modulo_y < HOVER_RADIUS)) {
        uint8_t const row_id = (event.y - Grid::mrgins.top + HOVER_RADIUS + 1) / m_cells.rect.h;
        uint8_t const column_id = (modulo_x < HOVER_RADIUS || modulo_x > m_cells.rect.w - HOVER_RADIUS) ? MAX_COLUMN_NB+1 : (event.x- Grid::mrgins.left) / m_cells.rect.w;

        if(row_id > m_grid.y+1 || column_id+1 > m_grid.x) return;

        m_borders.hor.data[row_id][column_id].second = true;
    }
}

void Grid::onQuit() {
    continueGame = 0;
}
