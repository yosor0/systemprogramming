#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "student.h"

int main_display();
void dbquery(char *);
void dbcreate(char *);
void update_id(char *);
void update_score(char *);
void update_name(char *);
int update_menu();
void update(char *);

int main(int argc, char *argv[])
{
	int c;
	while ((c = main_display()) != 4)
	{
		switch(c)
		{
			case 1 : dbquery(argv[1]);
					 break;
			case 2 : dbcreate(argv[1]);
					 break;
			case 3 : update_menu(argv[1]);
					 break;
			default : printf("\n잘못된 입력입니다\n");
					  printf("다시 입력해 주세요\n\n");
		}
	}
}

int main_display() 
{
	int select = 0;

	printf("학생 정보 데이터베이스\n\n");
	printf("1. 학생 정보 검색\n");
	printf("2. 학생 정보 입력\n");
	printf("3. 학생 정보 수정\n");
	printf("4. 프로그램 종료\n");
	printf("메뉴 번호 선택 >>> ");
	scanf("%d", &select);

	return select;
}

void dbcreate(char *data)
{
	char k;
	int fd;
	struct student rec;

	if ((fd = open(data, O_WRONLY | O_CREAT, 0640)) == -1) {
		perror(data);
		exit(1);
	}

	do {
		k = '\0';
		printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
		scanf("%d %s %d", &rec.id, rec.name, &rec.score);
		lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
		write(fd, &rec, sizeof(rec));
		printf("계속하시겠습니까?(Y/N)");
		scanf(" %c", &k);
	} while (k == 'Y' || k == 'y');

	close(fd);
	
}

void dbquery(char *data)
{
	printf("학생 정보 검색.\n");

	int fd, id;
	char k;
	struct student rec;

	if((fd = open(data, O_RDONLY)) == -1) {
	perror(data);
		exit(1);
	}

	do {
		printf("\n검색할 학생의 학번 입력 : ");
		if (scanf("%d", &id) == 1) {
			lseek(fd, (id - START_ID) * sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0))
				printf("학번:%d\t 이름:%s\t 점수:%d\n",
						rec.id, rec.name, rec.score);
			else printf("레코드 %d 없음\n", id);
		}
		else printf("입력 오류");

		printf("계속하시겠습니까?(Y/N)");
		scanf(" %c", &k);
	} while (k == 'Y' || k == 'y');

	close(fd);
}

void update_score(char *data) {
	printf("학생 정보 수정.\n");
	
	char j = '\0';
	int fd, id;
	struct student rec;

	if ((fd = open(data, O_RDWR)) == -1) {
		perror(data);
		exit(1);
	}
	do {
		printf("수정할 학생의 학번 입력 : ");
		if (scanf("%d", &id) == 1) {
			lseek(fd, (long) (id - START_ID) *sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
				printf("학번:%8d\t 이름:%4s\t 점수:%4d\n",
						rec.id, rec.name, rec.score);
				printf("새로운 점수 : ");
				scanf("%d", &rec.score);
					lseek(fd, (long) -sizeof(rec), SEEK_CUR);
					write(fd, &rec, sizeof(rec));
			}
			else 
				printf("레코드 %d 없음\n", id);
		}
		else printf("입력 오류\n");
		printf("계속하시겠습니까?(Y/N)");
		scanf("%c", &j);
	}
	while (j == 'y' || j == 'Y');

	close(fd);
}

int update_menu ()
{
	int select_update = 0;

	printf("무엇을 수정하시겠습니까?\n");
	printf("1. 학번\n");
	printf("2. 이름\n");
	printf("3. 점수\n");
	printf("4. 종료\n");
	printf("메뉴 번호 선택 >>> ");
	scanf("%d", &select_update);

	return select_update;
}

void update (char *data) 
{
	int i;
	while ((i = update_menu()) != 4) {
		switch(i) {
			case 1 : update_id(data);
					 break;
			case 2 : update_name(data);
					 break;
			case 3 : update_score(data);
					 break;
			default : printf("잘못된 입력입니다.\n");
					  printf("다시 입력해 주세요\n");
		}
	}
}

void update_name(char *data)
{
	char j = '\0';
	int fd, id;
	struct student rec;

	if ((fd = open(data, O_RDWR)) == -1) {
		perror(data);
		exit(1);
	}

	do {
	printf("수정할 학생의 이름 입력 : ");
	if (scanf("%d", &id) == 1) {
		lseek (fd, (long) (id - START_ID) * sizeof(rec), SEEK_SET);
		if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
				printf("학번:%8d\t 이름:%4s\t 점수:%4d\n",
						rec.id, rec.name, rec.score);
				printf("새로운 이름 : ");
				scanf("%s", &rec.name);
				lseek(fd, 2 * sizeof(rec), SEEK_SET);
				write(fd, &rec, sizeof(rec));
			}
			else printf("레코드 %d 없음\n", id);
	}else printf("입력 오류\n");
	printf("계속하시겠습니까?(Y/N)");
	scanf("%c", &j);
	}
	while (j == 'Y' || j == 'y');

	close(fd);
}

void update_id(char *data)
{
	char j = '\0';
	int fd, id;
	struct student rec;

	if ((fd = open(data, O_RDWR)) == -1) {
		perror(data);
		exit(1);
	}

	do {
	printf("수정할 학생의 학번 입력 : ");
	if (scanf("%d", &id) == 1) {
		lseek(fd, (long) (id - START_ID) * sizeof(rec), SEEK_SET);
		if((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
			printf("학번:%8d\t 이름:%4s\t 점수:%4d\n",
					rec.id, rec.name, rec.score);
			printf("새로운 학번 : ");
			scanf("%d", &rec.id);
			lseek(fd, 0L, SEEK_SET);
			write(fd, &rec, sizeof(rec));
		}
		else printf("레코드 %d 없음\n", id);
	}
	else printf("입력 오류\n");
	printf("계속하시겠습니까?(Y/N)");
	scanf("%c", &j);
	} while (j == 'y' || j == 'Y');

	close(fd);
}
