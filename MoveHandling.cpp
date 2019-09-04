/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "MoveHandling.h"

int moveUpToLimit(int pos, int min, int max, int speed,
                   bool* negSideHit, bool* posSideHit)
{
    int movedPos = pos + speed;
    if (movedPos < min)
    {
        if (negSideHit != nullptr) *negSideHit = true;
        return min;
    }
    if (movedPos > max)
    {
        if (posSideHit != nullptr) *posSideHit = true;
        return max;
    }
    return movedPos;
}

void paddleMoveHandler(bool isUp, SDL_Rect* rect)
{
    int speed = (C::paddlePixPerSec / C::FPS) * (isUp ? -1 : 1);
    rect->y = moveUpToLimit(rect->y, 0, C::windowH - C::paddleH, speed);
    return;
}

int ballMoveHandler(int* direction, SDL_Rect* ballrect, SDL_Rect* leftPaddleRect, SDL_Rect* rightPaddleRect) /// 0: normal. 1: Left scores. 2: Right scores.
{
    int Xspeed = (C::ballPixPerSec / C::FPS) * (((*direction) % 2) ? 1 : -1);  // Calculate speeds
    int Yspeed = (C::ballPixPerSec / C::FPS) * (((*direction) < 2) ? -1 : 1);

    bool hitSides[4] {false, false, false, false};  // Top, left, right, bottom

    int movedX = moveUpToLimit(ballrect->x, C::paddlePadding + C::paddleW, C::windowW - C::paddlePadding - C::paddleW - C::ballW,
                               Xspeed, hitSides+1, hitSides+2);  // Collision bounds is set to the paddles' X points
    int movedY = moveUpToLimit(ballrect->y, 0, C::windowH - C::ballW, Yspeed, hitSides, hitSides+3);

    ballrect->x = movedX;  // Change the position in order to check collision with paddles
    ballrect->y = movedY;

    int whoScored = 0;
    bool wasHit = false;

    int directionXisNeg = *direction < 2;    // Calculate direction by separating it into components, modifying them, and combining them
    int directionYisNeg = !(*direction % 2);

    if (hitSides[0] || hitSides[3])  // Bounce the ball by reversing the direction components once their axis is hit
    {
        directionYisNeg = !directionYisNeg;
        wasHit = true;
    }

    if (hitSides[1] || hitSides[2])
    {
        directionXisNeg = !directionXisNeg;
        SDL_Rect ballCollisionBox;  // The ball's collision box is one pixel bigger to support collision checking
        initRect(ballrect->x -1, ballrect->y -1, ballrect->w + 2, ballrect->h + 2, &ballCollisionBox);

        whoScored = ( hitSides[2] && !SDL_HasIntersection(rightPaddleRect, &ballCollisionBox)) ? 2 : whoScored;
        whoScored = ( hitSides[1] && !SDL_HasIntersection(leftPaddleRect, &ballCollisionBox)) ? 1 : whoScored;
        wasHit = true;
    }

    if (wasHit)
    {
        *direction = (2*directionXisNeg) + directionYisNeg;
    }

    return whoScored;
}
