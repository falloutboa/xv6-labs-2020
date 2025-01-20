#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	primefork(n, p);
	close(p[0]);
	for (int n = 3; n <= 35; n++) {
		write(p[1], n, sizeof(n));
	}
	exit(0);
}

void
primefork(int n, int p[2])
{
	printf("prime %d\n", n);
	int pid, status;
	pid = fork();
	if (pid == 0) {
		primefork(
	} else {
		while(1) {
			int buf;
			read(p[0], &buf, sizeof(buf));
			if (buf == 0) {
				close(p[0]);
				break;	
			}
			if (buf % n != 0){
				write(p[1], read_num, sizeof(int);
			}
		}
		close(p[1]);
	}
}
