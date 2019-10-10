/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "WindowAndDisplay.h"
#include "GameContext.h"

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

bool eventCheck(Uint32 event)
{
    return SDL_PeepEvents(0, 0, SDL_PEEKEVENT, event, event);
}

int FILTER_paddles(void* userdata, SDL_Event* event)
{
    if (!(CHECK_eventHasType(event, GameContext::EVENT_FRAME_BEGIN))) // Call once per frame
    {
        return 0;
    }

    static GameContext& game = *((GameContext*)userdata);

    for(int i = 0; i<2; i++)
    {
        if (game.kbStates[C::leftPaddleKeys[i]])  paddleMoveHandler(!((bool)i), &game.leftPaddleRect);
        if (game.kbStates[C::rightPaddleKeys[i]]) paddleMoveHandler(!((bool)i), &game.rightPaddleRect);
    }

    return 0;
}

int FILTER_stop(void* userdata, SDL_Event* event)
{
    if (event->type == SDL_QUIT || ((event->type == SDL_KEYDOWN) && (event->key.keysym.sym == SDLK_ESCAPE)))
    {
        static GameContext& game = *((GameContext*)userdata);
        game.stopApp = true;
        quit(game.windowObj, game.rendererObj);
    }

    return 0;
}
