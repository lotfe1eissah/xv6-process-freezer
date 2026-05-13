#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc , char *argv[]){
int p[2];
char buf[64];

if (pipe(p)<0){
	printf("pipe failed\n");
	exit(0);
	}
int pid = fork();
if (pid < 0){
	printf("fork failed\n");
	exit(0);
	}
if (pid == 0){
	close(p[1]);
	int n = read(p[0], buf, sizeof (buf) -1);
	if (n < 0){
		printf("child : read failed\n");
		close(p[0]);
		exit(0);
		}
	buf[n] = '\0';
	printf("child recived : %s",buf);
	close(p[0]);
	exit(0);
	} else {
		close(p[0]);
		char *msg = "hello from parent pipe";
		write(p[1], msg , strlen(msg));
		close(p[1]);
		wait(0);
		close(0);
		}
}
