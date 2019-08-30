/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "MoveHandling.h"

int moveAxisWithinBounds(int pos, int minimum, int maximum, int speed)
{
    int finalPos = pos + speed;
    if (finalPos < minimum)
    {
        return minimum;
    }
    if (finalPos > maximum)
    {
        return maximum;
    }
    return finalPos;
}

int moveAxisWithinBounds(int pos, int minimum, int maximum, int speed, bool* sideA, bool* sideB, int* excessDisplacement)
{
    int finalPos = pos + speed;
    if (finalPos < minimum)
    {
        *sideA = true;
        *excessDisplacement = finalPos - minimum;
        return minimum;
    }
    if (finalPos > maximum)
    {
        *sideB = true;
        *excessDisplacement = finalPos - maximum;
        return maximum;
    }
    return finalPos;
}

void moveWithinBounds(int Xspeed, int Yspeed, SDL_Rect* obj, SDL_Rect* boundary)
{
    obj->x = moveAxisWithinBounds(obj->x, boundary->x, (boundary->w) - (obj->w), Xspeed);
    obj->y = moveAxisWithinBounds(obj->y, boundary->y, (boundary->h) - (obj->h), Yspeed);
    return;
}

void moveWithinBounds(int Xspeed, int Yspeed, SDL_Rect* obj, SDL_Rect* boundary, bool hitSides[4], int excessDisplacements[2])
{
    obj->x = moveAxisWithinBounds(obj->x, boundary->x, (boundary->w) - (obj->w), Xspeed, &(hitSides[1]), hitSides+2, excessDisplacements);
    obj->y = moveAxisWithinBounds(obj->y, boundary->y, (boundary->h) - (obj->h), Yspeed, &(hitSides[0]), hitSides+3, excessDisplacements+1);
    return;
}

void paddleMoveHandler(bool isUp, SDL_Rect* rect)
{
    static SDL_Rect bounds;
    static bool first = true;
    if (first)
    {
        initRect(0, 0, C::windowW, C::windowH, &bounds);
        first = false;
    }

    int speed = (C::paddlePixPerSec / C::FPS) * (isUp ? -1 : 1);

    moveWithinBounds(0, speed, rect, &bounds);

    return;
}

int ballMoveHandler(int* direction, SDL_Rect* ballrect, SDL_Rect* leftPaddleRect, SDL_Rect* rightPaddleRect)  /// 0: normal. 1: Left scores. 2: Right scores.
{
    ///Calculate speed and final position.
    int Xspeed = (C::ballPixPerSec / C::FPS) * (((*direction) % 2) ? 1 : -1);
    int Yspeed = (C::ballPixPerSec / C::FPS) * (((*direction) < 2) ? -1 : 1);

    int whoScored = 0;

    int Xfinal = ballrect->x + Xspeed;
    int Yfinal = ballrect->y + Yspeed;

    bool hitSides[4] {false, false, false, false};
    int excessDisplacements[2] {0,0};
    int finalDir = 0;

    SDL_Rect copyObj;
    initRect(ballrect->x, ballrect->y, ballrect->w, ballrect->h, &copyObj);

    SDL_Rect bounds;
    initRect(C::paddlePadding + C::paddleW, 0, C::windowW - (C::paddlePadding + C::paddleW), C::windowH, &bounds);

    moveWithinBounds(Xspeed, Yspeed, &copyObj, &bounds, hitSides, excessDisplacements);  // If the ball has hit, it sticks.

    bool hitOnce = false;
    bool hitTwice = false;
    int hitIndex = 0;
    for(int i = 0; i<4; i++)
    {
        if (hitSides[i] && hitOnce)
        {
            hitOnce = false;
            hitTwice = true;
            break;
        }
        if (hitSides[i])
        {
            hitOnce = true;
            hitIndex = i;
        }
    }

    if(hitTwice)
    {
        switch (*direction)
        {
        case 0:
            finalDir = 3;
            break;
        case 3:
            finalDir = 0;
            break;
        case 1:
            finalDir = 2;
            break;
        case 2:
            finalDir = 1;
            break;
        }
    }

    else if(hitOnce)
    {
        switch (hitIndex)
        {
        case 0:
            finalDir = (*direction) + 2;
            break;
        case 3:
            finalDir = (*direction) - 2;
            break;
        case 1:
            finalDir = (*direction) + 1;
            break;
        case 2:
            finalDir = (*direction) - 1;
            break;
        }
    }

    if(hitOnce || hitTwice)
    {

        ///If left or right side hits, check to see if it collides with the paddle. If not, score.

        //std::cout << excessDisplacements[0] << "," << excessDisplacements[1] << " \n";
        int posX = ballrect->x + (-(excessDisplacements[0]) + ((-(excessDisplacements[0]) < 0) ? -1 : 1));
        int posY = ballrect->y + (-(excessDisplacements[1]) + ((-(excessDisplacements[1]) < 0) ? -1 : 1));
        copyObj.x--;  //Expand the width of the copy of the ball by 1, towards the center
        copyObj.y--;
        copyObj.w += 2;
        copyObj.h += 2;
        //Move the ball 1 pix left or right if it hits a goal. If it doesn't collide with the paddle, score.
        whoScored = ( hitSides[1] && (SDL_HasIntersection(leftPaddleRect, &copyObj) == SDL_FALSE )) ? 1 : whoScored;
        whoScored = ( hitSides[2] && (SDL_HasIntersection(rightPaddleRect, &copyObj) == SDL_FALSE )) ? 2 : whoScored;

        ballrect->x = posX;
        ballrect->y = posY;
        *direction = finalDir;
        return whoScored;
    }

    ballrect->x = Xfinal;
    ballrect->y = Yfinal;
    return 0;
}
