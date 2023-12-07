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

// Functions to be called to main to update wasdx input images on screen
void wPress(SDL_Window *wind, SDL_Renderer *rend);
void wRelease(SDL_Window *wind, SDL_Renderer *rend);
void aPress(SDL_Window *wind, SDL_Renderer *rend);
void aRelease(SDL_Window *wind, SDL_Renderer *rend);
void sPress(SDL_Window *wind, SDL_Renderer *rend);
void sRelease(SDL_Window *wind, SDL_Renderer *rend);
void dPress(SDL_Window *wind, SDL_Renderer *rend);
void dRelease(SDL_Window *wind, SDL_Renderer *rend);
void xPress(SDL_Window *wind, SDL_Renderer *rend);
void xRelease(SDL_Window *wind, SDL_Renderer *rend);

// Remove all images
void destroyImages(void){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


#endif