#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int main(int argc, char *argv[]){
if (argc < 2){
printf("usage : program tikcs\n");
exit(0);
}
int ticks = atoi(argv[1]);
if (ticks< 0)
ticks = 0;
sleep(ticks);
exit(0);
}
