/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "../include/GraphicsContext.h"

GraphicsContext::GraphicsContext()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    windowObj = SDL_CreateWindow(C::title, C::windowX, C::windowY, C::windowW, C::windowH, C::windowFlags);
    rendererObj = SDL_CreateRenderer(windowObj, -1, C::rendererFlags);

    // Clear screen with draw color
    SDL_SetRenderDrawColor(rendererObj, 0,0,0,255);
    SDL_RenderClear(rendererObj);
    SDL_RenderPresent(rendererObj);
}

GraphicsContext::~GraphicsContext()
{
    quit(windowObj, rendererObj);
}
