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
     extern int windowX;
     extern int windowY;
     extern int windowW;
     extern int windowH;
     extern int FPS;
     extern Uint32 windowFlags;
     extern Uint32 rendererFlags;

     extern Uint8 bgColors[];
     extern Uint8 gameObjectColors[];

     extern SDL_Scancode leftPaddleKeys[2];
     extern SDL_Scancode rightPaddleKeys[2];

    // May be calculated from previous constants
     extern int paddlePadding;
     extern int paddleH;
     extern int paddleW;
     extern int paddleY;
     extern int ballW;
     extern int ballPixPerSec;  /// Note: ball bounce currently depends in FPS being divisible by 60 int division
     extern int paddlePixPerSec;

     extern int leftPaddleDim[4]; // X,Y, W,H
     extern int rightPaddleDim[4];
     extern int ballDim[4];

     extern int bounceBoundaryDim[4];  // If the ball is inside this box, it is not in the goal.
}

#endif // CONSTANTS_H_INCLUDED
