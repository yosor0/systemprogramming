#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argvc, char *argv[])
{
	int child, pid, fd, status;

	pid = fork();
	if (pid == 0) {
		fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0600);
		dup2(fd, 1);
		close (fd);
		execvp(argv[2], &argv[2]);
		fprintf(stderr, "%s:실행 불가\n", argv[1]);
	} else {
		child = wait(&status);
		printf("[%d] 자식 프로세스 %d 종료\n", getpid(), child);
	}
}
