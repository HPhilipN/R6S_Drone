#include <iostream>
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

#include "clientNet.hpp"

static const int WIDTH = 640;
static const int HEIGHT = 480;
static const int YUV_FRAME_SIZE = (int)(WIDTH * HEIGHT * 1.5);
static const int FRAMERATE = 2;
// static int socket;
// static int stopFlag;
#define MAX 64

// static void* displayThread(void *arg){
//     SDL_Renderer* rend = *(SDL_Renderer**)arg;
//     SDL_Texture *cameraTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); 
//     while(stopFlag != 0){
//         char frameBuffer[YUV_FRAME_SIZE];
//         bzero(frameBuffer, YUV_FRAME_SIZE);
//         read(socket, frameBuffer, sizeof(frameBuffer));
//         SDL_UpdateTexture(cameraTexture, NULL, frameBuffer, WIDTH);
//     }
//     pthread_exit(NULL);
// }

/* Calculate a checksum for the buffer */
uint8_t netChecksum(char* buffer) {
    uint8_t result = 0;
    for (int i = 0; i < sizeof(buffer); i++) {
        result ^= buffer[i];
    }
    return result;
}

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

    SDL_Event event;

    // int ready;
    while(1){

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // char buff[1];
                // buff[0] = 'q';
                // write(socket, buff, sizeof(buff));
                SDL_DestroyTexture(cameraTexture);
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                SDL_Quit();
                return 0;
            }
        }

        

        char frameBuffer[YUV_FRAME_SIZE];
        bzero(frameBuffer, YUV_FRAME_SIZE);
        size_t bytesRead = recv(socket, frameBuffer, YUV_FRAME_SIZE, MSG_WAITALL);
        printf("Bytes Read: %zu, Receiver Checksum: %d\n", bytesRead, (int)netChecksum(frameBuffer));
        SDL_UpdateTexture(cameraTexture, NULL, frameBuffer, WIDTH);

        // Uint8* yBuffer = new Uint8[WIDTH * HEIGHT];
        // Uint8* uBuffer = new Uint8[WIDTH / 2 * HEIGHT / 2];
        // Uint8* vBuffer = new Uint8[WIDTH / 2 * HEIGHT / 2];
        // read(socket, yBuffer, sizeof(yBuffer));
        // read(socket, uBuffer, sizeof(uBuffer));
        // read(socket, vBuffer, sizeof(vBuffer));
        // SDL_UpdateYUVTexture(cameraTexture, nullptr, yBuffer, WIDTH, uBuffer, WIDTH / 2, vBuffer, WIDTH / 2);

        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, cameraTexture, NULL, NULL);

        SDL_RenderPresent(rend);

        char buff[1];
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_D]){
            if(keystates[SDL_SCANCODE_W]){
                printf("FWD\n");
                buff[0] = 'f';
                write(socket, buff, sizeof(buff));
            }
            if(keystates[SDL_SCANCODE_A]){
                printf("LEFT\n");
                buff[0] = 'l';
                write(socket, buff, sizeof(buff));
            }
            if(keystates[SDL_SCANCODE_S]){
                printf("RVRSE\n");
                buff[0] = 'b';
                write(socket, buff, sizeof(buff));
            }
            if(keystates[SDL_SCANCODE_D]){
                printf("Right\n");
                buff[0] = 'r';
                write(socket, buff, sizeof(buff));
            }else{
                buff[0] = 'n';
                write(socket, buff, sizeof(buff));
            }
        }else{
            if(keystates[SDL_SCANCODE_X]){
                buff[0] = 'q';
                write(socket,buff,sizeof(buff));
                // SDL_DestroyTexture(cameraTexture);
                // SDL_DestroyRenderer(rend);
                // SDL_DestroyWindow(win);
                // SDL_Quit();
                return 0;
            }
            buff[0] = 's';
            write(socket, buff, sizeof(buff));
        }

        SDL_Delay(30);

    }

    // SDL_DestroyTexture(cameraTexture);
    // SDL_DestroyRenderer(rend);
    // SDL_DestroyWindow(win);
    // SDL_Quit();

    return 0;
}