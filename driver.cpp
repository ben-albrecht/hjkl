#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "driver.h"

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

// SDL REQUIRES this signature for main
int main(int argc, char* args[]) {

    // Main Loop flag
    bool quit = false;

    bool stretch = false;

    // Event handler
    SDL_Event e;

    // Demonstration of stretching image to match screen size
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

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

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    stretch = false;
                    break;

                    case SDLK_j:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    stretch = false;
                    break;

                    case SDLK_k:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    stretch = false;
                    break;

                    case SDLK_l:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    stretch = false;
                    break;

                    case SDLK_SPACE:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE];
                    stretch = true;
                    break;
                }
            }
        } //  while (SDL_PolLEvent(&e) != 0

        if (stretch) {
            SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
        } else {
            //Apply the image
            /* Takes source surface (gCurrentSurface) and stamps a copy of it onto
            destination surface (gScreenSurface), which is displayed in gWindow */
            SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
        }
        // Necessary after any change to our window
        SDL_UpdateWindowSurface( gWindow );

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
        // Signature: (window caption, window x position,
        //            window y position, window width, window height,
        //            window is visible)
        gWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {

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

    return success;
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
        // Free up old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

bool loadMedia()
{
    bool success = true;

    // Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("images/press.bmp");
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    // Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL )
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    // Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL )
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    // Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL )
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    // Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL )
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    // Load colors surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE] = loadSurface("images/colors.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE] == NULL )
    {
        printf("Failed to load colors (space) image!\n");
        success = false;
    }
    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gCurrentSurface );
    gCurrentSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

