/**
A BSD 2-Clause License is in use here. See LICENSE.md for license information.
Copyright (c) 2019, SBcodework
All rights reserved.
**/

#include "GameContext.h"

// Watch this method in case it gets too long or complex
GameContext::GameContext(GraphicsContext* graphicsContext_)
{
    graphicsContext = graphicsContext_;
    windowObj = graphicsContext->windowObj;
    rendererObj = graphicsContext->rendererObj;

    /// Non-SDL Init
    srand(time(0));

    /// Init rects/textures/images

    leftPaddleRect.setter(C::leftPaddleDim);
    ballRect.setter(C::ballDim);
    rightPaddleRect.setter(C::rightPaddleDim);

    /// Game coniguration and events init

    ballDir = rand() % 4;  /// 0-1: Top, 2-3: bottom; even: left, odd: right. Example: 1 is top-left, 3 is bottom-right.

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

    EVENT_FRAME_BEGIN = SDL_RegisterEvents(2);  // Allocates a set of user-defined events
    EVENT_FRAME_END = EVENT_FRAME_BEGIN + 1;

    SDL_AddEventWatch(FILTER_stop, this);

    // Set up allResourceSDLrects to contain the SDL_Rect* members of our Rectf resources
    for(int i = 0; i < allResourceRects_size; i++)
    {
        allResourceSDLrects[i] = allResourceRects[i]->toSDL();
    }

    updateAllRectf();
    renderPresentRects(rendererObj, allResourceSDLrects, 3);

    countDown();
    SDL_AddEventWatch(FILTER_paddles, this);
}

// These are going to be assigned values in the constructor.
// This is here to avoid undefined behavior.
Uint32 GameContext::EVENT_FRAME_BEGIN = 0;
Uint32 GameContext::EVENT_FRAME_END = 0;

void GameContext::updateAllRectf()
{
    for(int i = 0; i < allResourceRects_size; i++)
    {
        allResourceRects[i]->updateSDL();
    }
}

void GameContext::countDown()
{
    for(int i = 0; i < 50 && !stopApp && !SDL_QuitRequested(); i++)  // Without SDL_QuitRequested(), the game doesn't quit if needed
    {
        if( !(i%10) ) std::cout << (5 - (i/10)) << "...\n";  // Every second, 5 times
        SDL_Delay(100);
    }

    if(!stopApp)  std::cout << "GO!\n";
}

void GameContext::pushBlankEvent(Uint32 type)
{
    SDL_Event event;
    event.type = type;
    SDL_PushEvent(&event);  // Event is copied to the queue, per SDL documentation
}

int GameContext::mainLoop()
{
    while(!stopApp)
    {

        if (errorPresent())
        {
            quit(windowObj, rendererObj);
            return 1;
        }

        SDL_PumpEvents();  // Update the event queue.

        kbStates = SDL_GetKeyboardState(0);
        mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        pushBlankEvent(EVENT_FRAME_BEGIN);

        /// Insert additional event handling code here

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);  // Clear all events, needed to stop the queue from overflowing.

        /// Insert handlers here

        handleScoring(ballMoveHandler(&ballDir, &ballRect, &leftPaddleRect, &rightPaddleRect));

        if(stopApp)
        {
            return 0;
        }

        updateAllRectf();
        renderPresentRects(rendererObj, allResourceSDLrects, 3);

        pushBlankEvent(EVENT_FRAME_END);
    }

    return 0;
}

void GameContext::handleScoring(int scoreCode)
{
    switch (scoreCode)
    {
    case 1:
        std::cout << " Right Scored!\nSCORE: " << leftScore << " VS " << ++rightScore << "\n";
        break;
    case 2:
        std::cout << " Left Scored!\nSCORE: " << ++leftScore << " VS " << rightScore << "\n";
        break;
    }
}

GameContext::~GameContext()
{
    //dtor
}
