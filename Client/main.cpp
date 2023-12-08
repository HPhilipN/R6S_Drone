#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <time.h>
#include <pthread.h>

#include "../CAR/network.hpp"

static const int WIDTH = 640;
static const int HEIGHT = 480;
static const int YUV_FRAME_SIZE = (int)(WIDTH * HEIGHT * 1.5);
static const int FRAMERATE = 30;

int main(){

    int socket = initClient();
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIDTH, HEIGHT, 0);
 
    
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // Set up SDL texture to hold the camera stream
    SDL_Texture *cameraTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); 

    while(1){
        uint8_t frameBuffer[YUV_FRAME_SIZE];
        read(socket, frameBuffer, sizeof(frameBuffer));

        SDL_UpdateTexture(cameraTexture, NULL, frameBuffer, WIDTH);

        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, cameraTexture, NULL, NULL);

        SDL_RenderPresent(rend);

        SDL_Delay(30);

    }

    SDL_DestroyTexture(cameraTexture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}