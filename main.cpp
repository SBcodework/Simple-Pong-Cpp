/**
BSD 2-Clause License
Copyright (c) 2019, SBcodework
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include <iostream>
#include <SDL.h>
#include <string>
#include <vector>
#include <time.h>

#include "Constants.h"
#include "NonWindowUtilities.h"

void displayUpdateRects(SDL_Renderer* renderer, SDL_Rect** rects, int number)
{
    Uint8* bg = C::bgColors;
    Uint8* boxColor = C::gameObjectColors;

    SDL_SetRenderDrawColor(renderer, bg[0], bg[1], bg[2], bg[3]);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, boxColor[0], boxColor[1], boxColor[2], boxColor[3]);

    for (int i = 0; i < number; i++)
    {
        SDL_RenderDrawRect(renderer, rects[i]);
    }

    SDL_RenderPresent(renderer);
    return;
}

bool errorPresent()
{
    const char* msg = SDL_GetError();
    if (msg[0] == '\0')
    {
        return false;
    }

    std::cout << "Error: " << msg << "\n";
    return true;
}

void quit(SDL_Window* win, SDL_Renderer* renderer)
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    return;
}

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

void moveWithinBounds(int Xspeed, int Yspeed, SDL_Rect* obj, SDL_Rect* boundary)  // If obj is outside of the boundary even a bit, obj is moved to limit.
{
    obj->x = moveAxisWithinBounds(obj->x, boundary->x, (boundary->w) - (obj->w), Xspeed);
    obj->y = moveAxisWithinBounds(obj->y, boundary->y, (boundary->h) - (obj->h), Yspeed);
    return;
}
                                                            /// hitSides is top to bottom, left to right. Top is 0, left is 1, right is 2, bottom is 3.
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

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* windowObj = SDL_CreateWindow(C::title, C::windowX, C::windowY, C::windowW, C::windowH, C::windowFlags);
    SDL_Renderer* rendererObj = SDL_CreateRenderer(windowObj, -1, C::rendererFlags);

    if (errorPresent())
    {
        quit(windowObj, rendererObj);
        return 1;
    }

    // Clear screen with draw color
    SDL_SetRenderDrawColor(rendererObj, 0,0,0,255);
    SDL_RenderClear(rendererObj);
    SDL_RenderPresent(rendererObj);

    /// Custom features here

    SDL_Rect leftPaddleRect, ballRect, rightPaddleRect;
    SDL_Rect* allResourceRects[3] {&leftPaddleRect,& ballRect, &rightPaddleRect};

    initRect(C::leftPaddleDim, &leftPaddleRect);
    initRect(C::ballDim, &ballRect);
    initRect(C::rightPaddleDim, &rightPaddleRect);

    bool leftPaddleKeyPresses[2] = {false, false};  // Up, down
    bool rightPaddleKeyPresses[2] = {false, false};

    //Pre-loop

    srand(time(0));
    int ballDir = rand() % 4;  /// 0-1: Top, 2-3: bottom; even: left, odd: right. Example: 1 is top-left, 3 is bottom-right.
    int scored = 0;
    int leftScore = 0;
    int rightScore = 0;

    /// ====================

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_Event e;
    SDL_Keycode ekey = 0;
    bool stopApp = false;

    displayUpdateRects(rendererObj, allResourceRects, 3);

    for(int i = 0; i < 5; i++)
    {
        std::cout << (5 - i) << "...\n";
        SDL_Delay(1000);
    }
    std::cout << "GO!\n";

    while(!stopApp)
    {

        if (errorPresent())
        {
            quit(windowObj, rendererObj);
            return 1;
        }

        for(Uint32 etype; SDL_PollEvent(&e); )
        {
            etype = e.type;

            if (etype == SDL_QUIT || (etype == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                quit(windowObj, rendererObj);
                return 0;
            }

            if (etype == SDL_KEYDOWN && e.key.repeat == SDL_FALSE)  /// Re-factor later, remove nested ifs
            {
                ekey = e.key.keysym.sym;
                for(int i = 0; i<2; i++)
                {
                    leftPaddleKeyPresses[i] = (ekey == C::leftPaddleKeys[i] ? true : leftPaddleKeyPresses[i]);
                    rightPaddleKeyPresses[i] = (ekey == C::rightPaddleKeys[i] ? true : rightPaddleKeyPresses[i]);
                }
            }

            if (etype == SDL_KEYUP && e.key.repeat == SDL_FALSE)
            {
                ekey = e.key.keysym.sym;
                for(int i = 0; i<2; i++)
                {
                    leftPaddleKeyPresses[i] = (ekey == C::leftPaddleKeys[i] ? false : leftPaddleKeyPresses[i]);
                    rightPaddleKeyPresses[i] = (ekey == C::rightPaddleKeys[i] ? false : rightPaddleKeyPresses[i]);
                }
            }

        }

        for (int i = 0; i < 2; i++)
        {
            if (leftPaddleKeyPresses[i])
            {
                paddleMoveHandler(!((bool)i), &leftPaddleRect);
            }
            if (rightPaddleKeyPresses[i])
            {
                paddleMoveHandler(!((bool)i), &rightPaddleRect);
            }
        }

        scored = ballMoveHandler(&ballDir, &ballRect, &leftPaddleRect, &rightPaddleRect);
        if (scored == 1)
        {
            rightScore++;
            std::cout << " Right Scored!\n";
        }
        if (scored == 2)
        {
            leftScore++;
            std::cout << " Left Scored!\n";
        }
        if(scored)
        {
            std::cout << "SCORE: " << leftScore << " VS " << rightScore << "\n";
        }

        displayUpdateRects(rendererObj, allResourceRects, 3);

    }
    return 0;
}
