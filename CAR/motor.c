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

void motorLeftFWD()
{
    printf("LEFT\n");
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
    printf("Right\n");
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
    printf("FWD\n");
    //left motor
    setValue(7, lo);
    setValue(8, hi);
    //right motor
    setValue(10, hi);
    setValue(9, lo);
    //pwm(motor speed)
    //pwmController();
    //pwmController();
}

void driveReverse()
{
    printf("RVRSE\n");
    //left motor
    setValue(7, hi);
    setValue(8, lo);
    //right motor
    setValue(10, lo);
    setValue(9, hi);
    //pwm(motor speed)
    //pwmController();
    //pwmController();
}

void stop()
{
    printf("STOP\n");
    //left motor
    setValue(7, lo);
    setValue(8, lo);
    //right motor
    setValue(10, lo);
    setValue(9, lo);
}
