#pragma once
#include <vector>
#include "../MyLibrary/Image.h"

struct Creature
{
    float m_xPosition = 0, m_yPosition = 0;
    float m_width = 0.5, m_height = 0.7;

    std::vector<Animation> m_animations;
    unsigned m_curAnimation = 0, m_curFrame = 0;
    float m_fFrameFraction = 0;

    float m_fXSpeed = 0;
    float m_fYSpeed = 0;

    void notifyEvent(SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            int nKeys = 0;
            const Uint8* pKeys = SDL_GetKeyboardState(&nKeys);
            m_fXSpeed = 0;
            m_fYSpeed = 0;
            if (pKeys[SDL_SCANCODE_DOWN])
                m_fYSpeed = 0.5;
            if (pKeys[SDL_SCANCODE_UP])
                m_fYSpeed -= 0.5;
            if (pKeys[SDL_SCANCODE_RIGHT])
                m_fXSpeed = 0.5;
            if (pKeys[SDL_SCANCODE_LEFT])
                m_fXSpeed -= 0.5;
            if (m_fXSpeed > 0)
            {
                m_curAnimation = 11;
            }
            if (m_fXSpeed < 0)
            {
                m_curAnimation = 9;
            }
            if (m_fYSpeed > 0)
            {
                m_curAnimation = 10;
            }
            if (m_fYSpeed < 0)
            {
                m_curAnimation = 8;
            }
            break;
        }
    }

    void animate(double fElapsedSeconds)
    {
        if (isMoving())
        {
            m_fFrameFraction += fElapsedSeconds * 10;
            if (m_fFrameFraction >= 1)
            {
                m_curFrame += (unsigned)m_fFrameFraction;
                m_fFrameFraction -= (unsigned)m_fFrameFraction;
            }
        }

        if (m_fXSpeed != 0)
        {
            m_xPosition += m_fXSpeed * fElapsedSeconds;
        }
        if (m_fYSpeed != 0)
        {
            m_yPosition += m_fYSpeed * fElapsedSeconds;
        }
    }

private:
    bool isMoving() const
    {
        return m_fXSpeed != 0 || m_fYSpeed != 0;
    }
};