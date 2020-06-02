#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	char *ptr;

	ptr = getenv("HOME");
	printf("HOME = %s \n", ptr);

	ptr = getenv("SHELL");
	printf("SHELL = %s \n", ptr);

	ptr = getenv("PATH");
	printf("PATH = %s \n", ptr);

	_exit(6);
}
