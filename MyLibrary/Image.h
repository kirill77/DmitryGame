#pragma once 

#include "../lodepng/lodepng.h"
#include "assert.h"
struct Pixel
{
    bool operator !=(const Pixel& other) const
    {
        return r != other.r || g != other.g || b != other.b || a != other.a;
    }
    unsigned char r, g, b, a;
};

struct Image
{
    void resize(int width, int height)
    {
        pixels.resize(width * height);
        m_width = width, m_height = height;
    }
    void setPixel(int x, int y, Pixel pixel)
    {
        pixels[x + y * m_width] = pixel;
    }
    Pixel getPixel(int x, int y)
    {
        return pixels[x + y * m_width];
    }

    std::vector<Pixel> pixels;
    unsigned int m_width = 0, m_height = 0;
    SDL_Surface* m_pSurface = nullptr;
    SDL_Texture* m_pTexture = nullptr;

    SDL_Surface* getSurface()
    {
        if (m_pSurface == nullptr)// Checks if pointer is equal to zero
        {
            assert(pixels.size() > 0);
            m_pSurface = SDL_CreateRGBSurfaceWithFormatFrom(&pixels[0], m_width, m_height, 32, m_width * 4, SDL_PIXELFORMAT_ABGR8888);
        }
        return m_pSurface;
    }
    SDL_Texture* getTexture(SDL_Renderer* pRenderer)
    {
        if (m_pTexture == nullptr)
        {
            m_pTexture = SDL_CreateTextureFromSurface(pRenderer, getSurface());
            if (m_pTexture == nullptr)
            {
                const char* sError = SDL_GetError();
                assert(false);
                sError = sError;
            }
        }
        return m_pTexture;
    }
    void Load(std::string filename)
    {
        std::vector<unsigned char> tmp;
        unsigned error = lodepng::decode(tmp, m_width, m_height, filename);
        for (int i = 0; i < tmp.size(); i += 4)
        {
            Pixel p;
            p.r = tmp[i];
            p.g = tmp[i + 1];
            p.b = tmp[i + 2];
            p.a = tmp[i + 3];
            pixels.push_back(p);
        }

    }
    void create(Image& bigImage, int bigX, int bigY, int smallWidth, int smallHeight)
    {
        resize(smallWidth, smallHeight);
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                if (bigX + x >= 0 && bigY + y >= 0)
                {
                    setPixel(x, y, bigImage.getPixel(bigX + x, bigY + y));
                }
            }
        }
    }
    bool AreYouEmpty()
    {
        Pixel firstPixel = getPixel(0, 0);
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                Pixel curPixel = getPixel(x, y);
                if (curPixel != firstPixel)
                {
                    return false;
                }
            }
        }   
        return true;
    }
};

struct Animation
{
    std::vector<Image> frames;
    void create(Image& bigImage, int frameWidth, int frameHeight, int row)
    {
        int nFrames = bigImage.m_width / frameWidth;
        for (int i = 0; i < nFrames; ++i) //loop
        {
            Image image;
            image.create(bigImage, i * frameWidth - 2, row * frameHeight - 14, frameWidth, frameHeight);
            if (!image.AreYouEmpty())
            {
                frames.push_back(image);
            }
        }
    }
};

void createAnimations(std::vector<Animation>& animations, Image& bigImage, int smallWidth, int smallHeight)
{
    int nAnimations = bigImage.m_height / smallHeight;
    animations.resize(nAnimations);
    for (int ia = 0; ia < nAnimations; ++ia) // loop 
    {
        Animation& animation = animations[ia];
        animation.create(bigImage, smallWidth, smallHeight, ia);
    }
}