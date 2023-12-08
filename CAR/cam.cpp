#include "cam.hpp"

static const int WIDTH = 640;
static const int HEIGHT = 480;
static const int YUV_FRAME_SIZE = (int)(WIDTH * HEIGHT * 1.5);
static const int FRAMERATE = 30;

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

void* camera(void* arg){
    int connection = *(int*)arg;

    char* videoPipeCommand;
    if (asprintf(&videoPipeCommand, "rpicam-vid --codec yuv420 -t 0 --width %d --height %d -o - -n --framerate %d", WIDTH, HEIGHT, FRAMERATE) == -1) {
        perror("Failed to create videoPipeCommand");
        pthread_exit(NULL);
    }

    // Create a videoPipe to capture camera data
    FILE *videoPipe = popen(videoPipeCommand, "r");
    if(!videoPipe){
        perror("ERROR: failed to open videoPipe");
        pthread_exit(NULL);
    }

    while(1){
        uint8_t frameBuffer[YUV_FRAME_SIZE];
        fread(frameBuffer, YUV_FRAME_SIZE, 1, videoPipe);

        write(connection, frameBuffer, sizeof(frameBuffer));

        // sleepForMs(30);
        
        // int ready;
        // do{
        //     read(connection, *ready, sizeof[ready]);
            
        // }while(ready != 1);

        char* buff[1];
        read(connection, buff, sizeof(buff));
    }
}