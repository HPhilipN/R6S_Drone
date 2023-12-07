#ifndef RCCONTROLLER_H
#define RCCONTROLLER_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

void* pollController(void*);
void startController();
void stopController();

#endif