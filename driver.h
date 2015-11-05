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

// Global variables

// The window we'll be rendering to
extern SDL_Window* gWindow;

// The window renderer
extern SDL_Renderer* gRenderer;

// Current displayed texture
extern SDL_Texture* gTexture;

// The surface contained by the window
extern SDL_Surface* gScreenSurface;

// The images that correspond to a keypress
extern SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
extern SDL_Surface* gCurrentSurface;

#endif
