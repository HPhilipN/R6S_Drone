//handles inputs (might delete)
#include "rcController.h"

pthread_t controllerThread;
pthread_mutex_t stopMutex = PTHREAD_MUTEX_INITIALIZER;
static bool stopFlag = false;

static void setStop(bool stop){
    pthread_mutex_lock(&stopMutex);
    stopFlag = stop;
    pthread_mutex_unlock(&stopMutex);
}

static bool getStop(){
    pthread_mutex_lock(&stopMutex);
    bool temp = stopFlag;
    pthread_mutex_unlock(&stopMutex);
    return temp;
}

void* pollController(void*){
    while(!getStop()){
        SDL_Event sdlEvent;

        while(SDL_PollEvent(&sdlEvent)){
            if(sdlEvent.type == SDL_QUIT){
                setStop(true);
            }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_W]){

        }
        if(keystates[SDL_SCANCODE_A]){

        }
        if(keystates[SDL_SCANCODE_S]){

        }
        if(keystates[SDL_SCANCODE_D]){

        }
    }
    pthread_exit(NULL);
}

void startController(){
    setStop(false);
    pthread_create(&controllerThread, NULL, pollController, NULL);
}

void stopController(){
    setStop(true);
    pthread_join(controllerThread, NULL);
}