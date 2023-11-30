#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// #include <conio.h>
#include <curses.h>

#include "motor.h"
#include "ctrlgpio.h"
#include "rcController.h"

// its not brokey we just tryna begin it
// also go make the main file :grin: yess
// wait i mean makefile ok
int main(){
    
    //exports the pins /sys/class/gpio/
    gpioExport(7);
    gpioExport(8);
    gpioExport(9);
    gpioExport(10);

    //sets the pin as either in || out 
    setDirection(7, dirOut);
    setDirection(8, dirOut);
    setDirection(9, dirOut);
    setDirection(10, dirOut);

    // user input to move both motors
    char input;
    int end = 0;

    while(end!=1){
        
        input = getchar();
        
        switch(input){
            case 'w': // forward
                stop();
                driveForward();
                break;
            case 's': // backward
                stop();
                driveReverse();
                break;
            case 'a': // left
                stop();
                motorLeftFWD();
                break;
            case 'd': // right
                stop();
                motorRightFWD();
                break;
            case 'x':
                end = 1;   
                stop();
                break;
            default:
                break;
        }
    }
    
    return 0;
}
