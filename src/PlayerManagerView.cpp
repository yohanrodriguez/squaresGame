#include "PlayerManagerView.h"

void PlayerManagerView::blit(SDL_Surface* dest) {

    PlayersManager* model = PlayersManager::singleton();

    SDL_FillRect(
        /* dst = */         dest,
        /* dst_rect = */    NULL,
        /* color = */       rageLib::sdl::Colors::get()->white
    );
    char buffer[5];

    SDL_Rect rect = {
        /* x = */   35,
        /* y = */   10,
        /* w = */   0,
        /* h = */   0
    };

    for(auto player : model->getList()) {

        SDL_Surface* playerName = TTF_RenderText_Shaded(
            /* font = */        (TTF_Font*) FontManager::singleton()->operator[]("default"),
            /* text = */        player->getName().c_str(),
            /* fg_color = */    {0,0,0,0},
            /* bg_color = */    {255,255,255,0});

        SDL_BlitSurface(
            /* src = */         playerName,
            /* src_rect = */    NULL,
            /* dst = */         dest,
            /* dst_rect = */    &rect
        );

        SDL_FreeSurface(playerName);

        SDL_Surface* colorIndicator = SDL_CreateRGBSurface(
            /* flags = */   SDL_SRCALPHA | SDL_HWSURFACE,
            /* w = */       10,
            /* h = */       10,
            32, 0, 0, 0, 0
        );

        SDL_FillRect(
             /* dst = */        colorIndicator,
             /* dst_rect = */   NULL,
             /* color = */      player->getColor()
         );

        rect.x = 5;
        rect.y += 12;

        SDL_BlitSurface(
            /* src = */         colorIndicator,
            /* src_rect = */    NULL,
            /* dst = */         dest,
            /* dst_rect = */    &rect
        );

        rect.y += 33;

        if(player == model->currentPlayer()) {
            SDL_Rect t_rect = {(int16_t) (rect.x + 5), (int16_t) (rect.y -28), 0, 0};
            SDL_BlitSurface(colorIndicator, NULL, dest, &t_rect);
        }

        SDL_FreeSurface(colorIndicator);

        std::string score("-> ");
        sprintf(buffer, "%d", player->getScore());
        score += buffer;

        SDL_Surface* playerScore = TTF_RenderText_Shaded(
            /* font = */        (TTF_Font*) FontManager::singleton()->operator[]("default"),
            /* text = */        score.c_str(),
            /* fg_color = */    {0,0,0,0},
            /* bg_color = */    {255,255,255,0}
        );

        SDL_BlitSurface(
            /* src = */         playerScore,
            /* src_rect = */    NULL,
            /* dst = */         dest,
            /* dst_rect = */    &rect
        );
        SDL_FreeSurface(playerScore);

        rect.x = 35;
        rect.y += 45;
    }
}
