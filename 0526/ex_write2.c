#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	printf("real user id : %d\n", getuid());
	printf("effective user id : %d\n", geteuid());
	FILE *fp = fopen("dum", "w");
	
	if(fp)
	{
		fprintf(fp, "Hello\n");
		fclose(fp);
	}
	else
	{
		printf("fopen error\n");
	}
	return 0;
}
