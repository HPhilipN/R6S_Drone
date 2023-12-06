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
#include "rcController.h"

static const int WIDTH = 640;
static const int HEIGHT = 480;

// its not brokey we just tryna begin it
// also go make the main file :grin: yess
// wait i mean makefile ok
int main(){
    
    // printf("1");
    //exports the pins /sys/class/gpio/
    gpioExport(7);
    gpioExport(8);
    gpioExport(9);
    gpioExport(10);

    for(int i = 7; i < 11; i++){
        if (gpioExport(i) == -1) {
        perror("Error exporting GPIO pin 7");
        exit(EXIT_FAILURE);
        }
    }
    // printf("2");
    // sets the pin as either in || out 
    setDirection(7, dirOut);
    setDirection(8, dirOut);
    setDirection(9, dirOut);
    setDirection(10, dirOut);
    // printf("3");
    

    // returns zero on success else non-zero
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
 
// camera code begin

    // // Set up SDL texture to hold the camera stream
    // SDL_Texture *cameraTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    // // Command to capture camera data
    // char command[100];
    // snprintf(command, sizeof(command), "rpicam-vid -t 0 --width %d --height %d -o - -n --framerate 30", WIDTH, HEIGHT);

    // // Create a pipe to capture camera data
    // FILE *pipe = popen(command, "r");
    // if (!pipe) {
    //     perror("Error opening pipe");
    //     SDL_DestroyTexture(cameraTexture);
    //     SDL_DestroyRenderer(rend);
    //     SDL_DestroyWindow(win);
    //     SDL_Quit();
    //     return -1;
    // }

    // // Main loop
    // SDL_Event event;
    // while (1) {
    //     // Read camera data from the pipe
    //     char buffer[WIDTH * HEIGHT * 3];
    //     size_t bytesRead = fread(buffer, 1, sizeof(buffer), pipe);

    //     // Update the texture with the new camera data
    //     SDL_UpdateTexture(cameraTexture, NULL, buffer, WIDTH * 3);

    //     // Clear the renderer
    //     SDL_RenderClear(rend);

    //     // Copy the texture to the renderer
    //     SDL_RenderCopy(rend, cameraTexture, NULL, NULL);

    //     // Present the renderer
    //     SDL_RenderPresent(rend);

    //     // Check for events (e.g., window close)
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             SDL_DestroyTexture(cameraTexture);
    //             SDL_DestroyRenderer(rend);
    //             SDL_DestroyWindow(win);
    //             SDL_Quit();
    //             pclose(pipe);
    //             return 0;
    //         }
    //     }
    // }

// camera code end


    // creates a surface to load an image into the main memory
    // SDL_Surface* surface;
 
    // please provide a path for your image
    // surface = IMG_Load("image.png");
 
    // loads image to our graphics hardware memory.
    // SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
 
    // clears main-memory
    // SDL_FreeSurface(surface);
 
    // let us control our image position
    // so that we can move it with our keyboard.
    // SDL_Rect dest;
 
    // connects our texture with dest to control position
    // SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
 
    // adjust height and width of our image box.
    // dest.w /= 6;
    // dest.h /= 6;
 
    // sets initial x-position of object
    // dest.x = (1000 - dest.w) / 2;
 
    // sets initial y-position of object
    // dest.y = (1000 - dest.h) / 2;
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    // int speed = 300;
 
    // animation loop
    while (!close) {
        // printf("here\n");
        SDL_Event event;
 
        // Events management
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                close = 1;
            }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_W] || keystates[SDL_SCANCODE_A] || keystates[SDL_SCANCODE_S] || keystates[SDL_SCANCODE_D]){
            if(keystates[SDL_SCANCODE_W]){
                // dest.y -= speed / 30;
                printf("FWD\n");
                driveForward();
            }
            if(keystates[SDL_SCANCODE_A]){
                // dest.x -= speed / 30;
                printf("LEFT\n");
                motorLeftFWD();
            }
            if(keystates[SDL_SCANCODE_S]){
                // dest.y += speed / 30;
                printf("RVRSE\n");
                driveReverse();
            }
            if(keystates[SDL_SCANCODE_D]){
                // dest.x += speed / 30;
                printf("Right\n");
                motorRightFWD();
            }
        }else{
            stop();
        }
 
        // right boundary
        // if (dest.x + dest.w > 1000)
            // dest.x = 1000 - dest.w;
 
        // left boundary
        // if (dest.x < 0)
            // dest.x = 0;
 
        // bottom boundary
        // if (dest.y + dest.h > 1000)
            // dest.y = 1000 - dest.h;
 
        // upper boundary
        // if (dest.y < 0)
            // dest.y = 0;
 
        // clears the screen
        SDL_RenderClear(rend);
        // SDL_RenderCopy(rend, tex, NULL, &dest);
 
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy texture
    // SDL_DestroyTexture(tex);
    // SDL_DestroyTexture(cameraTexture);
 
    // // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // // destroy window
    SDL_DestroyWindow(win);
     
    // // close SDL
    SDL_Quit();


    // gpioUnExport(7);
    // gpioUnExport(8);
    // gpioUnExport(9);
    // gpioUnExport(10);
    
// initialize_camera();
// capture_image();
// release_camera();

    return 0;
}
