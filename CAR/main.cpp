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

#include "motor.h"
#include "ctrlgpio.h"
#include "network.hpp"
#include "cam.hpp"
#include "control.hpp"

static const int WIDTH = 640;
static const int HEIGHT = 480;
static const int YUV_FRAME_SIZE = (int)(WIDTH * HEIGHT * 1.5);
static const int FRAMERATE = 2;
static int stopFlag = 0;

static void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

/* Calculate a checksum for the buffer */
uint8_t netChecksum(char* buffer) {
    uint8_t result = 0;
    for (int i = 0; i < sizeof(buffer); i++) {
        result ^= buffer[i];
    }
    return result;
}

static void* netCam(void* arg){
    int connection = *(int*)arg;
    // Command to capture camera data
    char* videoPipeCommand;
    if (asprintf(&videoPipeCommand, "rpicam-vid --codec yuv420 -t 0 --width %d --height %d -o - -n --framerate %d", WIDTH, HEIGHT, FRAMERATE) == -1) {
        perror("Failed to create videoPipeCommand");
        pthread_exit(NULL);
    }

    // Create a videoPipe to capture camera data
    FILE *videoPipe = popen(videoPipeCommand, "r");
    if (!videoPipe) {
        perror("Error opening videoPipe");
        pthread_exit(NULL);
    }

    while(stopFlag != 1){
        char frameBuffer[YUV_FRAME_SIZE];
        fread(frameBuffer, YUV_FRAME_SIZE, 1, videoPipe);
        printf("Sender Checksum: %d\n", (int)netChecksum(frameBuffer));
        write(connection, frameBuffer, sizeof(frameBuffer));
    }

    pthread_exit(NULL);
}

int main(){
    
    //exports the pins /sys/class/gpio/
    gpioExport(7);
    gpioExport(8);
    gpioExport(9);
    gpioExport(10);
    
    //export pwm done in motor controls

    
    // wait for udev
    sleepForMs(100);

    for(int i = 7; i < 11; i++){
        if (gpioExport(i) == -1) {
        perror("Error exporting GPIO pin 7");
        exit(EXIT_FAILURE);
        }
    }
    // sets the pin as either in || out 
    setDirection(7, dirOut);
    setDirection(8, dirOut);
    setDirection(9, dirOut);
    setDirection(10, dirOut);

// networking stuff
    int connection = initServer();
    // int connection = 0;

    // pthread_t cameraThread;
    // pthread_t controlThread;

    // pthread_create(&cameraThread, NULL, camera, &connection);
    // pthread_create(&controlThread, NULL, control, NULL);

// networking stuff end



    // // returns zero on success else non-zero
    // if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    //     printf("error initializing SDL: %s\n", SDL_GetError());
    // }
    // SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
    //                                    SDL_WINDOWPOS_CENTERED,
    //                                    SDL_WINDOWPOS_CENTERED,
    //                                    WIDTH, HEIGHT, 0);
 
    
    // // triggers the program that controls
    // // your graphics hardware and sets flags
    // Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // // creates a renderer to render our images
    // SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // // Set up SDL texture to hold the camera stream
    // SDL_Texture *cameraTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); 

    // // Command to capture camera data
    // char* videoPipeCommand;
    // if (asprintf(&videoPipeCommand, "rpicam-vid --codec yuv420 -t 0 --width %d --height %d -o - -n --framerate %d", WIDTH, HEIGHT, FRAMERATE) == -1) {
    //     perror("Failed to create videoPipeCommand");
    //     return -1;
    // }

    // // Create a videoPipe to capture camera data
    // FILE *videoPipe = popen(videoPipeCommand, "r");
    // if (!videoPipe) {
    //     perror("Error opening videoPipe");
    //     SDL_DestroyTexture(cameraTexture);
    //     SDL_DestroyRenderer(rend);
    //     SDL_DestroyWindow(win);
    //     SDL_Quit();
    //     return -1;
    // }

    // free(videoPipeCommand);

    pthread_t camThread;
    pthread_create(&camThread, NULL, netCam, &connection);

    // Main loop
    // SDL_Event event;
    while (1) {

        // // Check for events (e.g., window close)
        // while (SDL_PollEvent(&event)) {
        //     if (event.type == SDL_QUIT  || event.key.keysym.scancode == SDL_SCANCODE_X) {
        //         SDL_DestroyTexture(cameraTexture);
        //         SDL_DestroyRenderer(rend);
        //         SDL_DestroyWindow(win);
        //         SDL_Quit();
        //         pclose(videoPipe);
        //         return 0;
        //     }
        // }

        // // Read camera data from the videoPipe
        // char frameBuffer[YUV_FRAME_SIZE];
        // fread(frameBuffer, YUV_FRAME_SIZE, 1, videoPipe);
        // write(connection, frameBuffer, sizeof(frameBuffer));
        // SDL_UpdateTexture(cameraTexture, NULL, frameBuffer, WIDTH);

        // //  Fallback works
        //     // Uint8* yBuffer = new Uint8[WIDTH * HEIGHT];
        //     // Uint8* uBuffer = new Uint8[WIDTH / 2 * HEIGHT / 2];
        //     // Uint8* vBuffer = new Uint8[WIDTH / 2 * HEIGHT / 2];

        //     // fread(yBuffer, 1, WIDTH * HEIGHT, videoPipe);
        //     // fread(uBuffer, 1, WIDTH / 2 * HEIGHT / 2, videoPipe);
        //     // fread(vBuffer, 1, WIDTH / 2 * HEIGHT / 2, videoPipe);

        //     // write(connection, yBuffer, sizeof(yBuffer));
        //     // write(connection, uBuffer, sizeof(uBuffer));
        //     // write(connection, vBuffer, sizeof(vBuffer));

        //     // SDL_UpdateYUVTexture(cameraTexture, nullptr, yBuffer, WIDTH, uBuffer, WIDTH / 2, vBuffer, WIDTH / 2);
        // //  Fallback end

        // // Clear the renderer
        // SDL_RenderClear(rend);

        // // Copy the texture to the renderer
        // SDL_RenderCopy(rend, cameraTexture, NULL, NULL);

        // // Present the renderer
        // SDL_RenderPresent(rend);

        // const Uint8* keystates = SDL_GetKeyboardState(NULL);
        // if(keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_D]){
        //     if(keystates[SDL_SCANCODE_W]){
        //         printf("FWD\n");
        //         driveForward();
        //     }
        //     if(keystates[SDL_SCANCODE_A]){
        //         printf("LEFT\n");
        //         motorLeftFWD();
        //     }
        //     if(keystates[SDL_SCANCODE_S]){
        //         printf("RVRSE\n");
        //         driveReverse();
        //     }
        //     if(keystates[SDL_SCANCODE_D]){
        //         printf("Right\n");
        //         motorRightFWD();
        //     }
        // }else{
        //     stop();
        // }

        char buff[1];
        read(connection, buff, sizeof(buff));
        if(buff[0] == 'f'){
            printf("FWD\n");
            driveForward();
        }
        if(buff[0] == 'l'){
            printf("LEFT\n");
            motorLeftFWD();
        }
        if(buff[0] == 'b'){
            printf("RVRSE\n");
            driveReverse();
        }
        if(buff[0] == 'r'){
            printf("Right\n");
            motorRightFWD();
        }
        if(buff[0] == 's'){
            stop();
        }
        if(buff[0] == 'q'){
            stop();
            stopFlag = 1;
            return 0;
        }

        SDL_Delay(30);

        
    }


    pthread_join(camThread, NULL);
    return 0;
}
