#ifndef IMGREND_H
#define IMGREND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

void loadImage(const char *image, int xdim, int ydim, int xpos, int ypos);


#endif