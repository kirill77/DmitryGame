#pragma once
#include "Creature.h"
#include "../MyLibrary/Image.h"
struct Camera
{
    float m_xPosition = 0, m_yPosition = 0;
    float m_fScale = 200;
    void draw(Creature& creature, SDL_Renderer* pRenderer, double fElapsedSeconds)
    {
        creature.animate(fElapsedSeconds);
        Animation &curAnimation = creature.m_animations[creature.m_curAnimation];
        SDL_FRect destRect;
        destRect.x = (creature.m_xPosition + m_xPosition) * m_fScale;
        destRect.y = (creature.m_yPosition + m_yPosition) * m_fScale;
        destRect.w = (creature.m_width * m_fScale);
        destRect.h = (creature.m_height * m_fScale);
        unsigned int uFrame = creature.m_curFrame % curAnimation.frames.size();
        SDL_Texture* pTexture = curAnimation.frames[uFrame].getTexture(pRenderer);
        int errorcode = SDL_RenderCopyF(pRenderer, pTexture, NULL, &destRect);
        if (errorcode < 0)
        {
            const char* sError = SDL_GetError();
            assert(false);
            sError = sError;
        }
    }
};