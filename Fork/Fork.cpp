#include <chrono>
#define SDL_MAIN_HANDLED
#include "C:\GitHub\DmitryGame\SDL\SDL2-devel-2.0.22-VC\SDL2-2.0.22\include\SDL.h"
#pragma comment(lib, "C:\\GitHub\\DmitryGame\\SDL\\SDL2-devel-2.0.22-VC\\SDL2-2.0.22\\lib\\x64\\SDL2.lib");
#pragma comment(lib, "C:\\GitHub\\DmitryGame\\SDL\\SDL2-devel-2.0.22-VC\\SDL2-2.0.22\\lib\\x64\\SDL2main.lib");
#include "../MyLibrary/Image.h"
#include "Camera.h"

int main()
{
    int returnCode = SDL_Init(SDL_INIT_EVERYTHING);
    if (returnCode < 0)
    {
        return -1;
    }
 
    SDL_Window *pWindow = SDL_CreateWindow("DmitryGame", 100, 100, 800, 600, 0);
    Image bigImage;
    bigImage.Load("C:\\GitHub\\DmitryGame\\Media\\animatedSpearGirl.png");
    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    Camera camera;
    SDL_Event windowEvent;
    Creature creature;
    createAnimations(creature.m_animations, bigImage, 64, 64);
    auto prevTime = std::chrono::high_resolution_clock::now();
    for ( ; ; ) // loop
    {
        auto curTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedSeconds = curTime - prevTime;
        prevTime = curTime;

        SDL_RenderClear(pRenderer);

        camera.draw(creature, pRenderer, elapsedSeconds.count());
        
        SDL_PollEvent(&windowEvent);
        if (windowEvent.type == SDL_QUIT)
        {
            break;
        }
        creature.notifyEvent(windowEvent);
      
        SDL_RenderPresent(pRenderer);
    }

    SDL_DestroyWindow(pWindow);

    return 0;
}
