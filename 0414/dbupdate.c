#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
	int fd, id;
	char c;
	struct student rec;

	if (argc < 2) {
		fprintf(stderr, "사용법 : %s file\n", argv[0]);
	}

	if (fd = open(argv[1], O_RDWR) == -1) {
		perror(argv[1]);
		exit(2);
	}

	do {
		printf("수정할 학생의 학번 입력 : ");
		if (scanf("%d", &id) == 1) {
			lseek(fd, (long) (id-START_ID) * sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
				printf("학번:%8d\t 이름:%4s\t 점수:%4d\n", rec.id,
						rec.name, rec.score);
				printf("새로운 점수 : ");
				scanf("%d", &rec.score);
					lseek(fd, (long) -sizeof(rec), SEEK_CUR);
					write(fd, &rec, sizeof(rec));
			}
			else printf("레코드 %d 없음\n", id;
		}
		else printf("입력 오류\n");
		printf("계속하시겠습니까?(Y/N)");
		scanf(" %c", &c);
	}
	while (c == 'Y');

	close(fd);
	exit(0);
}
