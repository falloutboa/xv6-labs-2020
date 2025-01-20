#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void
filter(int *p)
{
	int prime;
	if (read(p[0], &prime, sizeof(prime)) == 0) {
		close(p[0]);
		exit(0);
	}	       
	printf("prime %d\n", prime);
	int next_p[2];
	pipe(next_p);
	if (fork() == 0) {
		close(next_p[1]);
		filter(next_p);
	} else {
		close(next_p[0]);
		int n;
		while (read(p[0], &n, sizeof(n)) != 0) {
			if (n % prime != 0) {
				write(next_p[1], &n, sizeof(n));
			}
		}
		close(next_p[1]);
		close(p[0]);
		wait(0);
	}
	return;
}
int
main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	if (fork() == 0) {
		close(p[1]);
		filter(p);
	} else {
		close(p[0]);
		for (int n = 2; n <= 35; n++) {
			write(p[1], &n, sizeof(n));
		}
		close(p[1]);
		wait(0);
	}
	exit(0);
}
