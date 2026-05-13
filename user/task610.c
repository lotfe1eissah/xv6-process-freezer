#include "kernel/types.h"
#include "user/user.h"

int main(){
        int fd[2];
        int pid;
        char msg[] = "hello from child";
        char buf[100];
        int n;
        pipe(fd);
        pid = fork();
        if (pid < 0){
                printf("failed\n");
                exit(1);
}
        if (pid==0){
                close(fd[0]);
                write(fd[1], msg , sizeof(msg));
                close(fd[1]);
                exit(0);
}       else{
                close(fd[1]);
                n= read(fd[0], buf , sizeof(buf));
                write (1,buf,n);
                close(fd[0]);
                wait(0);
                exit(0);
}
}
