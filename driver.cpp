#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "driver.h"

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Current displayed texture
SDL_Texture* gTexture = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The images that correspond to a keypress
SDL_Texture* gKeyPressTextures[ KEY_PRESS_SURFACE_TOTAL ];

// Current displayed image
SDL_Surface* gCurrentSurface = NULL;

// SDL REQUIRES this signature for main
int main(int argc, char* args[]) {

    // Main Loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    //Start up SDL and create window
    if( !init() )
    {
        printf("Failed to initialize!\n");
        return 1;
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf("Failed to load media!\n");
            return 1;
        }
    }

    gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];

    // While application is running
    while (!quit) {

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {

            // User requests quit
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }

            // User presses a key
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_h:
                    gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_LEFT];
                    break;

                    case SDLK_j:
                    gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DOWN];
                    break;

                    case SDLK_k:
                    gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_UP];
                    break;

                    case SDLK_l:
                    gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT];
                    break;

                    case SDLK_SPACE:
                    gTexture = gKeyPressTextures[KEY_PRESS_SURFACE_SPACE];
                    break;
                }
            }
        } //  while (SDL_PolLEvent(&e) != 0

        // Clear screen
        SDL_RenderClear(gRenderer);

        // Render texture to screen
        /* Stretches the image to full screen */
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        // Update screen
        SDL_RenderPresent(gRenderer);

    } // while (!quit)

    // Free up resources and close SDL
    close();

    return 0;
}

bool init() {
    bool success = true;

    // Initialize SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        /* Signature: (window caption, window x position,
                    window y position, window width, window height,
                    window is visible)
        */
        gWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create a renderer for window
            /* Signature:
               (Window, index of rendering driver or first one supporting flags [-1], requirement flags)
            */
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                /* Draw color to rendering context, r(ed), g(reen), b(lue), a(lpha) */
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading (separate SDL2 library)
                int imgFlags = IMG_INIT_PNG;
                if ( !(IMG_Init(imgFlags) & imgFlags )) {
                    printf("SDL_image could not be initialized! SDL_Error: %s\n", IMG_GetError());
                    success = false;
                } else {
                    // Get window surface
                    gScreenSurface = SDL_GetWindowSurface(gWindow);
                }
            }
        }
    }
    return success;
}


SDL_Texture* loadTexture(std::string path)
{
    // Final texture
    SDL_Texture* newTexture = NULL;

    // Load image at path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Create texture from surface pixels
        /* Create a texture from the loaded surface */
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        // Free up loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

SDL_Surface* loadSurface(std::string path) {

    // Final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image given by path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        // Convert surface to screen format
        /* Most BMP images are in 24bit format. This converts 24bit to 32bit image
           so that SDL does not have to convert it on the fly every blit */
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        // Free up loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

bool loadMedia()
{
    bool success = true;

    // Load default surface
    gKeyPressTextures[ KEY_PRESS_SURFACE_DEFAULT ] = loadTexture("images/press.bmp");
    if( gKeyPressTextures[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    // Load up surface
    gKeyPressTextures[KEY_PRESS_SURFACE_UP] = loadTexture("images/up.bmp");
    if (gKeyPressTextures[KEY_PRESS_SURFACE_UP] == NULL )
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    // Load down surface
    gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] = loadTexture("images/down.bmp");
    if (gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] == NULL )
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    // Load left surface
    gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] = loadTexture("images/left.bmp");
    if (gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] == NULL )
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    // Load left surface
    gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] = loadTexture("images/right.bmp");
    if (gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] == NULL )
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    // Load colors surface
    gKeyPressTextures[KEY_PRESS_SURFACE_SPACE] = loadTexture("images/colors.bmp");
    if (gKeyPressTextures[KEY_PRESS_SURFACE_SPACE] == NULL )
    {
        printf("Failed to load colors (space) image!\n");
        success = false;
    }
    return success;
}

void close()
{
    // Free loaded image from texture
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    // Free loaded image from surface
    SDL_FreeSurface( gCurrentSurface );
    gCurrentSurface = NULL;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

