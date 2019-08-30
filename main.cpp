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
#include "WindowAndDisplay.h"
#include "MoveHandling.h"

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

    renderPresentRects(rendererObj, allResourceRects, 3);

    for(int i = 0; i < 5; i++)
    {
        std::cout << (5 - i) << "...\n";

        for(int n = 0; n < 10; n++)
        {
            while(SDL_PollEvent(&e));  // Start a mini-event loop so we can quit when counting down
            {
                if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
                {
                    quit(windowObj, rendererObj);
                    return 0;
                }
            }

            SDL_Delay(100);  // Lower the delay so quiting can happen sooner, which is why above for loop is needed
        }
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

        renderPresentRects(rendererObj, allResourceRects, 3);

    }
    return 0;
}
