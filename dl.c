#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <getopt.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dir;
	struct stat st;
	char *path;
	char pathsize[BUFSIZ + 1];
	int c;
	int opt_a = 0;
	int opt_l = 0;

	while (1)
	{
		// getopt_long 옵션 
		static struct option long_options[] = 
		{
			{"all", no_argument, 0, 'a'},
			{"long", no_argument, 0, 'l'},
			{0, 0, 0, 0}
		};
		
		int option_index = 0;

		c = getopt_long (argc, argv, "al?", long_options, &option_index);

		if (c == -1)
			break;

		switch (c)
		{
			case 'a' : // a를 입력받으면 
				opt_a++; // opt_a 를 ++
				break;
			case 'l' : // l을 입력받으면 
				opt_l++; // opt_l 을  ++
				break;
			case '?' : // ?를 입력받으면 
				printf("    Usage     : dl [-option] [directory]\n"); 
				printf("Usable option : -a, -l\n");
				// 도움말 메세지 출력 
				return 0;
			default : 
				printf("option error\n");
				return 0;
		}
		
	}
	
	// 입력은 "dl [-옵션] [경로]" 순서로 받음 

	if (argc == 1) // 경로가 설정되지 않을경우 
		path = "."; // 현재 디렉토리를 경로로 설정 
	else if (argc == 2) { // argc 가 2일때 
		if (argv[1][0] == '-') // argv[1]의 첫번째 문자가 '-' 이면 
			path = "."; // 현재 디렉토리를 경로로 설정 
		else 
			path = argv[1]; // 아니라면 argv[1]을 경로로 설정 
	}
	else if (argc == 3) { // argc 가 3일때 
		if (argv[1][0] == '-') // argv[1]의 첫번째 문자가 '-' 이면 
			path = argv[2]; // argv[2]를 경로로 설정 
		else {
			printf("directory open error\n"); // 아니라면 오류메세지 출력 
			return 0;
		}
	}
	else {
		printf("directory open error\n");
		return 0;
	}

	if ((dp = opendir(path)) == NULL) {
		perror(path);
		return 0;
	}

	if (opt_l == 0) { // opt_l 이 0일 경우 
		while ((dir = readdir(dp)) != NULL)
		{
			if (opt_a == 0) // opt_a 가 0일 경우 
			{
				if (dir->d_name[0] == '.') // 숨김파일은 출력하지 않음 
				{
					continue;
				}
			}
			printf("%s\t", dir->d_name); // 파일명만 출력 
		}
		closedir(dp);
		printf("\n");
		return 0;
	}

	else if (opt_l == 1) { // opt_l 이 1일 경우 
		while ((dir = readdir(dp)) != NULL)
		{
			if (opt_a == 0) // opt_a 가 0일 경우 
			{
				if (dir->d_name[0] == '.') // 숨김파일은 출력하지 않음 
				{				
					continue;	
				}
			}
			sprintf(pathsize, "%s/%s", path, dir->d_name);
			if (lstat(pathsize, &st) < 0)
				perror(pathsize);
			else
				printStat(pathsize, dir->d_name, &st); 
				// printStat 함수를 통해 파일의 자세한 정보를 출력 
		}
		return 0;
	}

	printf("option input error\n");
	printf("Usage option :-a, -l\n");

	return 0;
}

// -l 옵션을 통해 파일의 자세한 정보 출력 
void printStat(char *pathname, char *file, struct stat *st) 
{
	printf("%5ld ", st->st_blocks);
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%3ld ", st->st_nlink);
	printf("%s %s ", getpwuid(st->st_uid)->pw_name,
			getgrgid(st->st_gid)->gr_name);
	printf("%9ld ", st->st_size);
	printf("%.12s ", ctime(&st->st_mtime) + 4);
	if (type(st->st_mode) == 'd')
		printf("%s/\n", file); // 파일의 타입이 디렉토리라면 파일명 뒤에 '/' 출력 
	else 
		printf("%s\n", file); // 아니라면 파일명만 출력 
}

char type(mode_t mode) // 타입 
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
}

char* perm(mode_t mode) // 권한 
{
	int i;
	static char perms[10];

	strcpy(perms, "---------");
	
	for (i = 0; i < 3; i++) {
		if (mode & (S_IREAD >> i*3))
			perms[i*3] = 'r';
		if (mode & (S_IWRITE >> i*3))
			perms[i*3+1] = 'w';
		if (mode & (S_IEXEC >> i*3))
			perms[i*3+2] = 'x';
	}
	return (perms);
}

// ** 참고 자료 및 사이트 **
// 수업 자료 dir_list/list2.c
// 수업 자료 getopt_ex/getopt_long_ex1.c
// soooprmx.com/archives/4993
// withcoding.com/89
// egloos.zum.com/rabe/v/1374613
