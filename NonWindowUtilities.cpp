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
