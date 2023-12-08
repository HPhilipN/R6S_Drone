#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include "motor.h"
#include "ctrlgpio.h"

//pin 10 & 8 clockwise
//pin 7 & 9 counter clockwise
//TODO maybe add flags for motor state?
void motorLeftFWD()
{
    
    //left motor
    setValue(7, hi);
    setValue(8, lo);
    //right motor
    setValue(10, hi);
    setValue(9, lo);
    //pwm(motor speed)
    //L
    //pwmController();
    //R
    //pwmController();
}

void motorRightFWD()
{

    //left motor
    setValue(7, lo);
    setValue(8, hi);
    //right motor
    setValue(10, lo);
    setValue(9, hi);
    //pwm(motor speed)
    //pwmController();
    //pwmController();
}

void driveForward()
{

    //left motor
    setValue(7, lo);
    setValue(8, hi);
    //right motor
    setValue(10, hi);
    setValue(9, lo);
    //pwm(motor speed)
    pwmController(0, 1000, 255);
    pwmController(1, 1000, 255);
    pwmEnable(1);
    pwmEnable(0);
}

void driveReverse()
{
    
    //left motor
    setValue(7, hi);
    setValue(8, lo);
    //right motor
    setValue(10, lo);
    setValue(9, hi);
    //pwm(motor speed)
    pwmController(0, 1000, 64);
    pwmController(1, 1000, 64);
    pwmEnable(0);
    pwmEnable(1);
}

void stop()
{

    //left motor
    setValue(7, lo);
    setValue(8, lo);
    //right motor
    setValue(10, lo);
    setValue(9, lo);

    pwmController(0, 1000, 0);
    pwmController(1, 1000, 0);
    pwmDisable(1);
    pwmDisable(0);
}
