#ifndef COLORS_H
#define COLORS_H

#include <string>
#include <SDL.h>

enum Color
{
    BASE03,
    BASE02,
    BASE01,
    BASE00,
    BASE0,
    BASE1,
    BASE2,
    BASE3,
    YELLOW,
    ORANGE,
    RED,
    MAGENTA,
    VIOLET,
    BLUE,
    CYAN,
    GREEN,
    COLORS_TOTAL
};

// Wrapper function for making shapes of a preset color
void SetRenderDrawColor(SDL_Renderer* renderer, Color color, Uint8 alpha = 0xFF);

#endif
