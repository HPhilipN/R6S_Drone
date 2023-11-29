#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <ctrlgpio.h>


// //write to file 
// static void writeNreadToFile(const char* fileName, const char* value)
// {
// 	FILE *pFile = fopen(fileName, "w");
// 	fprintf(pFile, "%s", value);
// 	fclose(pFile);
// }

// //reads file
// static int readLineFromFile(char* fileName, char* buff, unsigned int maxLength)
// {
// 	FILE *file = fopen(fileName, "r");
// 	int bytes_read = getline(&buff, &maxLength, file);
// 	fclose(file);
// 	return bytes_read;
// }

static int readNwriteFile(const char *fname, const char *wdata)
{
	int fd;
	fd = open(fname, O_WRONLY | O_NONBLOCK);
	if(fd < 0)
		printf("cannot open file %s...%d\r\n", fname, fd);

	write(fd, wdata, strlen(wdata));
	close(fd);
	return 0;
}


int gpioExport(int gpio_pin)
{
	char gpio_str[4];
	sprintf(gpio_str, "%d" ,gpio_pin);
	return readNwriteFile(pinPath pinExport, gpio_str);
}

int gpioUnExport(int gpio_pin)
{
	char gpio_str[4];
	sprintf(gpio_str, "%d" ,gpio_pin);
	return readNwriteFile(pinPath pinUnExport, gpio_str);
}

int setDirection(int gpio_pin, const char* dir)
{
	char path_str[40];
	sprintf(path_str, "%s/gpio%d%s", pinPath, gpio_pin, pinDir);
	return readNwriteFile(path_str, dir);
}

int setValue(int gpio_pin, const char* value)
{
	char path_str[40];
	sprintf(path_str, "%s/gpio%d%s", pinPath, gpio_pin, pinValue);
	return readNwriteFile(path_str, value);
}

int setEdge(int gpio_pin, const char* edge)
{
	char path_str[40];
	sprintf(path_str, "%s/gpio%d%s", pinPath, gpio_pin, edge);
	return readNwriteFile(path_str, edge);
}


int pinFdtoVal(int gpio_pin)
{
	int fd;
	char fname[40];
	sprintf(fname, "%s/gpio%d%s", pinPath, gpio_pin, pinValue);
	fd = open(fname, O_RDONLY | O_NONBLOCK);
	if(fd < 0)
		printf("could not open file %s...%d\r\n", fname, fd);

	return fd; 
}


