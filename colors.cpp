#include <SDL.h>
#include <string>
#include "colors.h"

void SetRenderDrawColor(SDL_Renderer* renderer, Color color, Uint8 alpha) {
    Uint8 r = 0xFF;
    Uint8 g = 0xFF;
    Uint8 b = 0xFF;

    switch(color)
    {
        default:
            printf("%d is not a valid color!\n", color); break;
        case BASE03:
            r = 0; g = 43; b = 54; break;
        case BASE02:
            r = 7; g = 54; b =  66; break;
        case BASE01:
            r = 88; g = 110; b =117; break;
        case BASE00:
            r = 101; g = 123; b =131; break;
        case BASE0:
            r = 131; g = 148; b =150; break;
        case BASE1:
            r = 147; g = 161; b =161; break;
        case BASE2:
            r = 238; g = 232; b =213; break;
        case BASE3:
            r = 253; g = 246; b = 227; break;
        case YELLOW:
            r = 181; g = 137; b = 0; break;
        case ORANGE:
            r = 203; g = 75; b =  22; break;
        case RED:
            r = 220; g = 50; b =  47; break;
        case MAGENTA:
            r = 211; g = 54; b =  130; break;
        case VIOLET:
            r = 108; g = 113; b = 196; break;
        case BLUE:
            r = 38; g =  139; b = 210; break;
        case CYAN:
            r = 42; g =  161; b = 152; break;
        case GREEN:
            r = 133; g = 153; b = 0; break;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
}

