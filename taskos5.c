#include "kernel/types.h"
#include "user/user.h"

int main (){
        int pid;
        pid = fork();
        if (pid < 0){
                printf("fork failed.\n");
}
        if (pid==0){
                char *args[] = {"ls" , 0};
                exec ("ls", args);
                printf("exec failed.\n");
                exit(1);
}       else {
                wait(0);
                printf("child finish");
}
        exit(0);
}
