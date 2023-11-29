#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include <motor.h>
#include <ctrlgpio.h>

//pin 10 & 8 clockwise
//pin 7 & 9 counter clockwise

void motorLeftFWD()
{
    printf("LEFT");
    //left motor
    setValue(GPIO7, hi);
    setValue(GPIO8, lo);
    //right motor
    setValue(GPIO10, hi);
    setValue(GPIO9, lo);
    //pwm(motor speed)

}

void motorRightFWD()
{
    printf("Right");
    //left motor
    setValue(GPIO7, hi);
    setValue(GPIO8, lo);
    //right motor
    setValue(GPIO10, hi);
    setValue(GPIO9, lo);
    //pwm(motor speed)
}

void driveForward()
{
    printf("FWD");
    //left motor
    setValue(GPIO7, hi);
    setValue(GPIO8, lo);
    //right motor
    setValue(GPIO10, hi);
    setValue(GPIO9, lo);
    //pwm(motor speed)
}

void driveReverse()
{
    printf("RVRSE+1");
    //left motor
    setValue(GPIO7, hi);
    setValue(GPIO8, lo);
    //right motor
    setValue(GPIO10, lo);
    setValue(GPIO9, hi);
    //pwm(motor speed)
}

//TODO function that handles motor speed 
//cause these shitty ass motors might be running at different speeds
void motorspeed(){

}