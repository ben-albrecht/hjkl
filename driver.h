#ifndef DRIVER_H
#define DRIVER_H

#include <SDL.h>
#include <string>

// Fire up SDL & create window
bool init();

// Load media
bool loadMedia();

// Free media and clean up SDL
void close();

// Loads an individual image
SDL_Surface* loadSurface(std::string path);

// Loads an individual image as a texture
/* This utilizes fast flexible hardware-based rendering */
SDL_Texture* loadTexture(std::string path);

// Key press surfaces consants
enum KeyPressTexture
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_SPACE,
    KEY_PRESS_SURFACE_TOTAL
};

#endif
