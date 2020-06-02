#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp = fopen("dum", "w");

	if (fp)
	{
		fprintf(fp, "Hello\n");
		fclose(fp);
	}
	else
	{
		printf("foopen error\n");
	}
	return 0;
}
