/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "WindowAndDisplay.h"

void renderPresentRects(SDL_Renderer* renderer, SDL_Rect** rects, int number)
{
    Uint8* bg = C::bgColors;
    Uint8* boxColor = C::gameObjectColors;

    SDL_SetRenderDrawColor(renderer, bg[0], bg[1], bg[2], bg[3]);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, boxColor[0], boxColor[1], boxColor[2], boxColor[3]);

    for (int i = 0; i < number; i++)
    {
        SDL_RenderDrawRect(renderer, rects[i]);
    }

    SDL_RenderPresent(renderer);
    return;
}

bool errorPresent()
{
    const char* msg = SDL_GetError();
    if (msg[0] == '\0')
    {
        return false;
    }

    std::cout << "Error: " << msg << "\n";
    return true;
}

void quit(SDL_Window* win, SDL_Renderer* renderer)
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    return;
}
