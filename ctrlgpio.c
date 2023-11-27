#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>



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

