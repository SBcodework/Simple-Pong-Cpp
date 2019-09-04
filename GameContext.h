/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "NonWindowUtilities.h"
#include "WindowAndDisplay.h"
#include "GraphicsContext.h"
#include "MoveHandling.h"

#include <time.h>

//class GraphicsContext;

class GameContext
{
    public:
        GameContext(GraphicsContext* graphicsContext_);
        GraphicsContext* graphicsContext = nullptr;

        SDL_Window* windowObj = nullptr;
        SDL_Renderer* rendererObj = nullptr;

        SDL_Rect leftPaddleRect, ballRect, rightPaddleRect;
        SDL_Rect* allResourceRects[3] {&leftPaddleRect, & ballRect, &rightPaddleRect};

        bool leftPaddleKeyPresses[2] = {false, false};  // Up, down
        bool rightPaddleKeyPresses[2] = {false, false};
        bool stopApp = false;

        int ballDir = 0;  /// 0-1: Top, 2-3: bottom; even: left, odd: right. Example: 1 is top-left, 3 is bottom-right.
        int scored = 0, leftScore = 0, rightScore = 0;
        int mouseX = 0, mouseY = 0;

        const Uint8* kbStates = nullptr;
        Uint32 mouseState = 0;

        static Uint32 EVENT_FRAME_BEGIN;
        static Uint32 EVENT_FRAME_END;
        static Uint32 EVENT_SCORE;


        virtual ~GameContext();

        void countDown();

        void pushBlankEvent(Uint32 type);
        void handleScoring(int scoreCode);

        int mainLoop();

    protected:

    private:
};

#endif // GAMECONTEXT_H
