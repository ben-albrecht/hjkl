#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include "driver.h"
#include "ltexture.h"

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}


LTexture::~LTexture()
{
    // Deallocate
    free();
}


bool LTexture::loadFromFile(std::string path)
{
    // Deallocate previous texture
    free();

    // Final texture
    SDL_Texture* newTexture = NULL;

    // Load image at given path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE,SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Free up loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    mTexture = newTexture;
    return newTexture;
}


void LTexture::free()
{
    // Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}


void LTexture::render(int x, int y)
{
    /* This is the primary reason we needed wrapper */
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y , mWidth, mHeight };
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}


int LTexture::getWidth()
{
    return mWidth;
}


int LTexture::getHeight()
{
    return mHeight;
}
