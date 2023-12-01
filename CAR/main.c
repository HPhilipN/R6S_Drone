#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

// #include <conio.h>
#include <curses.h>
#include <ncurses.h>

#include "motor.h"
#include "ctrlgpio.h"
#include "rcController.h"

#define SIZE 4
// pressed boolean array, 0123 -> wasd
bool pressed[SIZE] = {0}; 
bool motors = false;

// Function to handle key presses
void handleKeyPress(int key) {
    switch (key) {
        case 'w':
            pressed[0] = true;
            motors = true;
            break;
        case 'a':
            pressed[1] = true;
            motors = true;
            break;
        case 's':
            pressed[2] = true;
            motors = true;
            break;
        case 'd':
            pressed[3] = true;
            motors = true;
            break;
        default:
            break;
    }
}

// Function to handle key releases
void handleKeyRelease(int key) {

    if(motors){
        stop();
        motors = false;
        printw("STOP\n");
    }

    switch (key) {
        case 'w':
            pressed[0] = false;
            stop();
            break;
        case 'a':
            pressed[1] = false;
            stop();
            break;
        case 's':
            pressed[2] = false;
            stop();
            break;
        case 'd':
            pressed[3] = false;
            stop();
            break;
        default:
            break;
    }
}

// its not brokey we just tryna begin it
// also go make the main file :grin: yess
// wait i mean makefile ok
int main(){
    
    bool postMotor = false;

    initscr();  // Initialize ncurses
    cbreak();   // Line buffering disabled
    noecho();   // Don't display characters as they are typed
    timeout(7); // blocking keyboard input
    int key = 0;

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
    //sets the pin as either in || out 
    setDirection(7, dirOut);
    setDirection(8, dirOut);
    setDirection(9, dirOut);
    setDirection(10, dirOut);

    // user input to move both motors
    char input;
    int end = 0;
    bool keyRelease = false;

    while(1){

        key = getch(); // Get keyboard input
        if (key != ERR) {
            // Key is pressed
            handleKeyPress(key);

        }else{
            handleKeyRelease('w');
            handleKeyRelease('s');
            handleKeyRelease('a');
            handleKeyRelease('d');
        }

        // Perform actions based on key states
        if (pressed[0]) {
            // Move drone forward
            printw("FWD\n");
            refresh();
            driveForward();

        }

        if (pressed[1]) {
            // Move drone left
            printw("LEFT\n");
            refresh();
            motorLeftFWD();
        }

        if (pressed[2]) {
            // Move drone backward
            printw("RVRSE\n");
            refresh();
            driveReverse();
        }

        if (pressed[3]) {
            // Move drone right
            printw("Right\n");
            refresh();
            motorRightFWD();
        }

        // refresh(); // Refresh screen

        //usleep(10000); // Sleep for a short duration to control loop speed
    }

    endwin(); // End ncurses
    gpioUnExport(7);
    gpioUnExport(8);
    gpioUnExport(9);
    gpioUnExport(10);
    // while(1){
        
    //     input = getchar();
        
    //     switch(input){
    //         case 'w': // forward
    //             stop();
    //             driveForward();
    //             break;
    //         case 's': // backward
    //             stop();
    //             driveReverse();
    //             break;
    //         case 'a': // left
    //             stop();
    //             motorLeftFWD();
    //             break;
    //         case 'd': // right
    //             stop();
    //             motorRightFWD();
    //             break;
    //         case 'x':
    //             end = 1;   
    //             stop();
    //             break;
    //         default:
    //             break;
    //     }
    // }
    
    return 0;
}
