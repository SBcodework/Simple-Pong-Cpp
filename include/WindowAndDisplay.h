/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#ifndef WINDOWANDDISPLAY_H_INCLUDED
#define WINDOWANDDISPLAY_H_INCLUDED

#include "SDL.h"
#include "Constants.h"
#include "MoveHandling.h"

#include <iostream>

/// Draws rects to the screen and updates it.
void renderPresentRects(SDL_Renderer* renderer, SDL_Rect** rects, int number);

/// Checks if an error is present. Also prints the error to the console.
bool errorPresent();

/// Destroys the win and renderer objects.
void quit(SDL_Window* win, SDL_Renderer* renderer);

/// Checks if an event is in the queue.
bool eventCheck(Uint32 event);


/// Below functions are called once an event is added to the queue. They must return int and take void*, SDL_Event*.

/// For quitting the game. Userdata is a GameContext*.
int FILTER_stop(void* userdata, SDL_Event* event);

/// For moving the paddles. Userdata is a GameContext*.
int FILTER_paddles(void* userdata, SDL_Event* event);

#endif // WINDOWANDDISPLAY_H_INCLUDED
