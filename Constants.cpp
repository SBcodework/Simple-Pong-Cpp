/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "Constants.h"

namespace C  // Constants.
{
    char title[] {"Pong!"};

    // Below values should be whole numbers, but they are floats for convience to avoid excessive type casting.
    float windowX = SDL_WINDOWPOS_UNDEFINED;
    float windowY = SDL_WINDOWPOS_UNDEFINED;
    float windowW = 900.f;
    float windowH = 630.f;
    float FPS = 60.f;  // Frames per second.
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    Uint8 bgColors[] {0,0,0,255};  // Format: R, G, B, Alpha (Transparency) value. Alpha of 255 is solid, 0 is invisible.
    Uint8 gameObjectColors[] {255,0,0,255};

    SDL_Scancode leftPaddleKeys[2] {SDL_SCANCODE_Q, SDL_SCANCODE_A};
    SDL_Scancode rightPaddleKeys[2] {SDL_SCANCODE_O, SDL_SCANCODE_L};

    // May be calculated from previous constants
    float paddlePadding = 50.f;
    float paddleH = 200.f;
    float paddleW = 50.f;
    float paddleY = (windowH/2.f) - (paddleH/2.f);
    float ballW = 50.f;
    float ballPixPerSec = 610.f;
    float paddlePixPerSec = 1000.f;

    float leftPaddleDim[4] {paddlePadding, paddleY, paddleW, paddleH}; // X,Y, W,H
    float rightPaddleDim[4] {windowW - paddlePadding - paddleW, paddleY, paddleW, paddleH};
    float ballDim[4] {(windowW/2.f) - (ballW/2.f), (windowH/2.f) - (ballW/2.f), ballW, ballW};

    // If the ball is inside this box, it is not in the goal.
    float bounceBoundaryDim[4] {paddlePadding + paddleW, 0.f, windowW - (2.f*(paddlePadding - paddleW))};
}
