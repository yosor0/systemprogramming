#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argvi[])
{
	char **ptr;
	extern char **environ;

	for (ptr = environ; *ptr != 0; ptr++)
		printf("%s \n", *ptr);

	exit(0);
}
