#include "cam.hpp"

static const int WIDTH = 640;
static const int HEIGHT = 480;
static const int YUV_FRAME_SIZE = (int)(WIDTH * HEIGHT * 1.5);
static const int FRAMERATE = 30;

// static void sleepForMs(long long delayInMs)
// {
//     const long long NS_PER_MS = 1000 * 1000;
//     const long long NS_PER_SECOND = 1000000000;
//     long long delayNs = delayInMs * NS_PER_MS;
//     int seconds = delayNs / NS_PER_SECOND;
//     int nanoseconds = delayNs % NS_PER_SECOND;
//     struct timespec reqDelay = {seconds, nanoseconds};
//     nanosleep(&reqDelay, (struct timespec *) NULL);
// }

void* camera(void* arg){
    // int connection = *(int*)arg;

    // // char* buff = "guh";
    // // while(1){
    // //     write(connection, buff, sizeof(buff));
    // // }
    // // pthread_exit(NULL);


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

    // char* videoPipeCommand;
    // if (asprintf(&videoPipeCommand, "rpicam-vid --codec yuv420 -t 0 --width %d --height %d -o - -n --framerate %d", WIDTH, HEIGHT, FRAMERATE) == -1) {
    //     perror("Failed to create videoPipeCommand");
    //     pthread_exit(NULL);
    // }

    // // Create a videoPipe to capture camera data
    // FILE *videoPipe = popen(videoPipeCommand, "r");
    // if(!videoPipe){
    //     perror("ERROR: failed to open videoPipe");
    //     pthread_exit(NULL);
    // }

    // SDL_Event event;
    // while(1){
    //     // char frameBuffer[YUV_FRAME_SIZE];
    //     // bzero(frameBuffer, YUV_FRAME_SIZE);
    //     // fread(frameBuffer, YUV_FRAME_SIZE, 1, videoPipe);

    //     // write(connection, frameBuffer, sizeof(frameBuffer));

    //     // sleepForMs(30);


    //     // Check for events (e.g., window close)
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT  || event.key.keysym.scancode == SDL_SCANCODE_X) {
    //             SDL_DestroyTexture(cameraTexture);
    //             SDL_DestroyRenderer(rend);
    //             SDL_DestroyWindow(win);
    //             SDL_Quit();
    //             pclose(videoPipe);
    //             return 0;
    //         }
    //     }

    //     // Read camera data from the videoPipe
    //     char frameBuffer[YUV_FRAME_SIZE];
    //     fread(frameBuffer, YUV_FRAME_SIZE, 1, videoPipe);
    //     SDL_UpdateTexture(cameraTexture, NULL, frameBuffer, WIDTH);
    //     // Clear the renderer
    //     SDL_RenderClear(rend);
    //     // Copy the texture to the renderer
    //     SDL_RenderCopy(rend, cameraTexture, NULL, NULL);
    //     // Present the renderer
    //     SDL_RenderPresent(rend);
    //     SDL_Delay(30);

        
        
    //     // int ready;
    //     // do{
    //     //     read(connection, *ready, sizeof[ready]);
            
    //     // }while(ready != 1);

    //     // char buff[1];
    //     // do{
    //     //     read(connection, buff, sizeof(buff));
    //     // }while(buff[0] != 'a');

    //     // char buff[3] = {'g', 'u', 'h'};
    //     // write(connection, buff, sizeof(buff));
    // }
}