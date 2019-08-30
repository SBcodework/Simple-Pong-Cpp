/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#ifndef WINDOWANDDISPLAY_H_INCLUDED
#define WINDOWANDDISPLAY_H_INCLUDED

#include "SDL.h"
#include "Constants.h"

#include <iostream>

void renderPresentRects(SDL_Renderer* renderer, SDL_Rect** rects, int number);

/// Also prints the error to the console.
bool errorPresent();

/// Destroys the win and renderer objects.
void quit(SDL_Window* win, SDL_Renderer* renderer);



#endif // WINDOWANDDISPLAY_H_INCLUDED
