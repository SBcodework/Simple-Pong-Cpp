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

/// Returns the position of a point with a given speed. If it is beyond a limit, it is set to that limit.
/// Optional SideHit parameters available to check what side was hit.
int moveUpToLimit(int pos, int min, int max, int speed,
                  bool* negSideHit = nullptr, bool* posSideHit = nullptr);

/// Receives a direction and the paddle's rectangle. This should be called per frame, except when the paddle is idle.
void paddleMoveHandler(bool isUp, SDL_Rect* rect);

/// Moves and bounces the ball. This should be called per frame.
/// This function returns scoring data. 0: normal. 1: Left scores. 2: Right scores.
/// Direction uses top-bottom, left-right indexing on the corners of the ball's rectangle.
int ballMoveHandler(int* direction, SDL_Rect* ballrect, SDL_Rect* leftPaddleRect, SDL_Rect* rightPaddleRect);

#endif // MOVEHANDLING_H_INCLUDED
