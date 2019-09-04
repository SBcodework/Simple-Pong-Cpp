#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include "SDL.h"
#include "Constants.h"
#include "WindowAndDisplay.h"
#include "NonWindowUtilities.h"

class GraphicsContext
{
    public:
        GraphicsContext();
        virtual ~GraphicsContext();

        SDL_Window* windowObj = nullptr;
        SDL_Renderer* rendererObj = nullptr;

    protected:

    private:
};

#endif // GRAPHICSCONTEXT_H
