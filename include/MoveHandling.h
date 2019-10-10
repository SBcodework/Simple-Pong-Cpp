/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#ifndef MOVEHANDLING_H_INCLUDED
#define MOVEHANDLING_H_INCLUDED

#include "SDL.h"
#include "Constants.h"
#include "NonWindowUtilities.h"

/**
Float implementation of SDL_Rect, which stores x,y,w,h.
Objects of this class stores a SDL_Rect object, whose pointer can be obtained by
the method toSDL().
Before you operate on the SDL_Rect, you should call the updateSDL() method.
**/
struct Rectf
{
    float x, y, w, h;
    SDL_Rect SDLrect;

    Rectf(float X, float Y, float W, float H);
    Rectf();

    SDL_Rect* toSDL();

    void updateSDL();

    void setter(float X, float Y, float W, float H);

    void setter(float* values);
};

/// Returns the position of a point with a given speed. If it is beyond a limit, it is set to that limit.
/// Optional SideHit parameters available to check what side was hit.
float moveUpToLimit(float pos, float min, float max, float speed,
                  bool* negSideHit = nullptr, bool* posSideHit = nullptr);

/// Moves the paddle up or down within limits.
/// Receives a direction and the paddle's rectangle. This should be called per frame, except when the paddle is idle.
void paddleMoveHandler(bool isUp, Rectf* rect);

/// Moves and bounces the ball. This should be called per frame.
/// This function returns scoring data. 0: normal. 1: Left scores. 2: Right scores.
/// Direction uses top-bottom, left-right indexing on the corners of the ball's rectangle.
int ballMoveHandler(int* direction, Rectf* ballrect, Rectf* leftPaddleRect, Rectf* rightPaddleRect);

#endif // MOVEHANDLING_H_INCLUDED
