#include <stdio.h>

#define MAXLINE 80

int main(int argc, char *argv[])
{
	FILE *fp;
	int line = 0;
	char buffer[MAXLINE];

	if (argc != 2)
	{
		fprintf(stderr, "line  
