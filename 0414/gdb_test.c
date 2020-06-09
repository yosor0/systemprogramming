#include <stdio.h>
#include <stdlib.h>
#define MAX 256

int main()
{
	int n;
	char *buf;
	FILE *fp;

	if((fp = fopen("/etc/hosts", "r")) == NULL) {

