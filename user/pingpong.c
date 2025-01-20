#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p[2];
	char buf[64];
	char buf2[64];
	pipe(p);
	
	int pid, status;
	pid = fork();
	if (pid == 0) {
		int n = read(p[0], buf2, sizeof(buf2));
		close(p[0]);
		buf2[n] = '\0';
		printf("%d: received %s\n", pid, buf2);
		write(p[1], "pong", 4);
		close(p[1]);
		exit(0);
	} else {
		write(p[1], "ping", 4);
		close(p[1]);
		wait(&status);
		int n = read(p[0], buf, sizeof(buf));
		close(p[0]);
		buf[n] = '\0';
		printf("%d: received %s\n", pid, buf);
	}
	
	exit(0);
}
