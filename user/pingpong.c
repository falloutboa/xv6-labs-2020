#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p2c[2];
	int c2p[2];
	char buf[64];
	pipe(p2c);
	pipe(c2p);
	
	if (fork() == 0) {
		int n = read(p2c[0], buf, sizeof(buf));
		close(p2c[0]);
		buf[n] = '\0';
		printf("%d: received %s\n", getpid(), buf);
		write(c2p[1], "pong", 4);
		close(c2p[1]);
		exit(0);
	} else {
		write(p2c[1], "ping", 4);
		close(p2c[1]);
		wait(0);
		int n = read(c2p[0], buf, sizeof(buf));
		close(c2p[0]);
		buf[n] = '\0';
		printf("%d: received %s\n", getpid(), buf);
	}
	
	exit(0);
}
