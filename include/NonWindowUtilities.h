/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#ifndef NONWINDOWUTILITIES_H_INCLUDED
#define NONWINDOWUTILITIES_H_INCLUDED

#include "SDL.h"

void initRect(int x, int y, int w, int h, SDL_Rect* output);

/// Dimensions is an array of 4 sizes representing the x,y,w,h of a SDL_Rect.
void initRect(int* dimensions, SDL_Rect* output);


bool CHECK_eventHasType(SDL_Event* event, Uint32 type);
bool CHECK_keyDown(SDL_Event* event);
bool CHECK_keyUp(SDL_Event* event);

bool CHECK_eventHasKey(SDL_Event* event, SDL_Keycode key);
bool CHECK_eventHasKey(SDL_Event* event, SDL_Scancode key);

#endif // NONWINDOWUTILITIES_H_INCLUDED
