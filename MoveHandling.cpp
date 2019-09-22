/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "MoveHandling.h"
#include <iostream>

Rectf::Rectf(float X, float Y, float W, float H)
{
    x = X;
    y = Y;
    w = W;
    h = H;
}

Rectf::Rectf() {}

SDL_Rect* Rectf::toSDL()
{
    return &SDLrect;
}

void Rectf::updateSDL()
{
    SDLrect.x = (int)x;
    SDLrect.y = (int)y;
    SDLrect.w = (int)w;
    SDLrect.h = (int)h;
}

void Rectf::setter(float X, float Y, float W, float H)
{
    x = X;
    y = Y;
    w = W;
    h = H;
}

void Rectf::setter(float* values)
{
    x = values[0];
    y = values[1];
    w = values[2];
    h = values[3];
}

float moveUpToLimit(float pos, float min, float max, float speed,
                   bool* negSideHit, bool* posSideHit)
{
    float movedPos = pos + speed;
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

void paddleMoveHandler(bool isUp, Rectf* rect)
{
    float speed = (C::paddlePixPerSec / C::FPS) * (isUp ? -1.f : 1.f);  // Gets the pixel speed per frame, and applies the appropiate sign.
    rect->y = moveUpToLimit(rect->y, 0.f, C::windowH - C::paddleH, speed);  // The paddles only move along the Y axis.
    return;
}

int ballMoveHandler(int* direction, Rectf* ballrect, Rectf* leftPaddleRect, Rectf* rightPaddleRect) /// 0: normal. 1: Left scores. 2: Right scores.
{
    float Xspeed = (C::ballPixPerSec / C::FPS) * (((*direction) % 2) ? 1.f : -1.f);  // Calculate signed speeds
    float Yspeed = (C::ballPixPerSec / C::FPS) * (((*direction) < 2) ? -1.f : 1.f);

    bool hitSides[4] {false, false, false, false};  // Top, left, right, bottom

    float movedX = moveUpToLimit(ballrect->x, C::paddlePadding + C::paddleW, C::windowW - C::paddlePadding - C::paddleW - C::ballW,
                               Xspeed, hitSides+1, hitSides+2);  // Collision bounds is set to the paddles' surfaces
    float movedY = moveUpToLimit(ballrect->y, 0.f, C::windowH - C::ballW, Yspeed, hitSides, hitSides+3);

    ballrect->x = movedX;  // Change the position in order to check collision with paddles.
    ballrect->y = movedY;  // These will not be changed later in this function, so they are return values.

    int whoScored = 0;

    if (hitSides[0] || hitSides[3]) // When top or bottom is hit
    {
        *direction += hitSides[0] ? 2 : -2;  // Bounce the ball by reversing the direction components once their axis is hit
    }

    if (hitSides[1] || hitSides[2]) // When left or right is hit
    {
        *direction += hitSides[1] ? 1 : -1;
        SDL_Rect ballCollisionBox;  // The ball's collision box is one pixel bigger to support collision checking
        initRect(ballrect->x -1.f, ballrect->y -1.f, ballrect->w + 2.f, ballrect->h + 2.f, &ballCollisionBox);

        whoScored = ( hitSides[2] && !SDL_HasIntersection(rightPaddleRect->toSDL(), &ballCollisionBox)) ? 2 : whoScored;
        whoScored = ( hitSides[1] && !SDL_HasIntersection(leftPaddleRect->toSDL(), &ballCollisionBox)) ? 1 : whoScored;
    }

    return whoScored;
}
