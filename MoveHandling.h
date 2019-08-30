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

/// Returns "speed" + "pos", which represents motion along one axis. If the final position is beyond a limit, min or max, the function
/// returns the nearest limit.
/// Units are in pixels, and pixels/frame for speed.
int moveAxisWithinBounds(int pos, int minimum, int maximum, int speed);

/// See above. If a limit (side) is hit, "sideA" or "sideB" is set to true, where "sideA" represents the minimum limit's side.
/// ExcessDisplacement is a measure of how much the ball is beyond a limit if it is. If it is within bounds, it is not changed.
int moveAxisWithinBounds(int pos, int minimum, int maximum, int speed, bool* sideA, bool* sideB, int* excessDisplacement);

/// Uses the above function(s) to simulate collision motion with a boundary.
/// Collision only occurs when "obj" is not fully contained by "boundary".
/// Int units are in pixels/frame.
void moveWithinBounds(int Xspeed, int Yspeed, SDL_Rect* obj, SDL_Rect* boundary);

/// See above. "HitSides" indexing is top to bottom, left to right. Top is 0, left is 1, right is 2, bottom is 3.
void moveWithinBounds(int Xspeed, int Yspeed, SDL_Rect* obj, SDL_Rect* boundary, bool hitSides[4], int excessDisplacements[2]);

/// Receives a direction and the paddle's rectangle. This should be called per frame, except when the paddle is idle.
void paddleMoveHandler(bool isUp, SDL_Rect* rect);

/// Moves and bounces the ball. This should be called per frame.
/// This function returns scoring data. 0: normal. 1: Left scores. 2: Right scores.
/// Direction uses top-bottom, left-right indexing on the corners of the ball's rectangle.
int ballMoveHandler(int* direction, SDL_Rect* ballrect, SDL_Rect* leftPaddleRect, SDL_Rect* rightPaddleRect);

#endif // MOVEHANDLING_H_INCLUDED
