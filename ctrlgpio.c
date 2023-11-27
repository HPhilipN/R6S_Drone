#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define GPIO7 "/sys/class/gpio/gpio7"
#define GPIO8 "/sys/class/gpio/gpio8"
#define GPIO9 "/sys/class/gpio/gpio9"
#define GPIO10 "/sys/class/gpio/gpio10"

//pwm pins

#define GPIO12 "/sys/class/gpio/gpio12"
#define GPIO13 "/sys/class/gpio/gpio13"

//write to file 
static void writeToFile(const char* fileName, const char* value)
{
	FILE *pFile = fopen(fileName, "w");
	fprintf(pFile, "%s", value);
	fclose(pFile);
}

//reads file
static int readLineFromFile(char* fileName, char* buff, unsigned int maxLength)
{
	FILE *file = fopen(fileName, "r");
	int bytes_read = getline(&buff, &maxLength, file);
	fclose(file);
	return bytes_read;
}