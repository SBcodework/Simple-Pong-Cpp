/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "Constants.h"

namespace C// Constants
{
    char title[] {"Pong!"};
    int windowX = SDL_WINDOWPOS_UNDEFINED;
    int windowY = SDL_WINDOWPOS_UNDEFINED;
    int windowW = 1200;
    int windowH = 800;
    int FPS = 60;
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    Uint8 bgColors[] {0,0,0,255};
    Uint8 gameObjectColors[] {255,0,0,255};

    SDL_Scancode leftPaddleKeys[2] {SDL_SCANCODE_Q, SDL_SCANCODE_A};
    SDL_Scancode rightPaddleKeys[2] {SDL_SCANCODE_O, SDL_SCANCODE_L};

    // May be calculated from previous constants
    int paddlePadding = 50;
    int paddleH = 200;
    int paddleW = 50;
    int paddleY = (windowH/2) - (paddleH/2);
    int ballW = 50;
    int ballPixPerSec = 600;  /// Note: ball bounce currently depends in FPS being divisible by 60 int division
    int paddlePixPerSec = 1000;

    int leftPaddleDim[4] {paddlePadding, paddleY, paddleW, paddleH}; // X,Y, W,H
    int rightPaddleDim[4] {windowW - paddlePadding - paddleW, paddleY, paddleW, paddleH};
    int ballDim[4] {(windowW/2) - (ballW/2), (windowH/2) - (ballW/2), ballW, ballW};

    int bounceBoundaryDim[4] {paddlePadding + paddleW, 0, windowW - (2*(paddlePadding - paddleW))};  // If the ball is inside this box, it is not in the goal.
}
