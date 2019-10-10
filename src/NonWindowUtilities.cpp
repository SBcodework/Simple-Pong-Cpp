/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "NonWindowUtilities.h"

void initRect(int x, int y, int w, int h, SDL_Rect* output)
{
    output->x = x;
    output->y = y;
    output->w = w;
    output->h = h;
    return;
}

void initRect(int* dimensions, SDL_Rect* output)
{
    output->x = dimensions[0];
    output->y = dimensions[1];
    output->w = dimensions[2];
    output->h = dimensions[3];
    return;
}

bool CHECK_eventHasType(SDL_Event* event, Uint32 type)
{
    return event->type == type;
}

bool CHECK_keyDown(SDL_Event* event)
{
    return event->type == SDL_KEYDOWN;
}

bool CHECK_keyUp(SDL_Event* event)
{
    return event->type == SDL_KEYUP;
}

bool CHECK_eventHasKey(SDL_Event* event, SDL_Keycode key)
{
    return (event->key.keysym.sym == key);
}

bool CHECK_eventHasKey(SDL_Event* event, SDL_Scancode key)
{
    return (event->key.keysym.scancode = key);
}
