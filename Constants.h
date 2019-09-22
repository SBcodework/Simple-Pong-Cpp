/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include "SDL.h"

namespace C
{
     extern char title[];
     extern float windowX;
     extern float windowY;
     extern float windowW;
     extern float windowH;
     extern float FPS;
     extern Uint32 windowFlags;
     extern Uint32 rendererFlags;

     extern Uint8 bgColors[];
     extern Uint8 gameObjectColors[];

     extern SDL_Scancode leftPaddleKeys[2];
     extern SDL_Scancode rightPaddleKeys[2];

    // May be calculated from previous constants
     extern float paddlePadding;
     extern float paddleH;
     extern float paddleW;
     extern float paddleY;
     extern float ballW;
     extern float ballPixPerSec;  /// Note: ball bounce currently depends in FPS being divisible by 60 int division
     extern float paddlePixPerSec;

     extern float leftPaddleDim[4]; // X,Y, W,H
     extern float rightPaddleDim[4];
     extern float ballDim[4];

     extern float bounceBoundaryDim[4];  // If the ball is inside this box, it is not in the goal.
}

#endif // CONSTANTS_H_INCLUDED
