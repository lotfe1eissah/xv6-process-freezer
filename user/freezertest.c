#include "kernel/types.h"
#include "user/user.h"

void
delay(int n)
{
  volatile int i;
  for(i = 0; i < n * 1000000; i++){
  }
}

int
main(int argc, char *argv[])
{
  int pid = fork();

  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){
    int i = 0;
    while(1){
      printf("child running %d\n", i++);
      delay(1);
    }
  }

  delay(5);

  printf("parent: freezing child pid %d\n", pid);
  if(freeze(pid) < 0){
    printf("freeze failed\n");
    kill(pid);
    wait(0);
    exit(1);
  }

  printf("parent: child should stop printing now\n");
  delay(5);

  printf("parent: unfreezing child pid %d\n", pid);
  if(unfreeze(pid) < 0){
    printf("unfreeze failed\n");
    kill(pid);
    wait(0);
    exit(1);
  }

  printf("parent: child should print again\n");
  delay(5);

  kill(pid);
  wait(0);

  printf("freezertest done\n");
  exit(0);
}
