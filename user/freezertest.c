#include "kernel/types.h"
#include "user/user.h"

void
delay(int n)
{
  volatile int i;
  for(i = 0; i < n * 5000000; i++){
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
      delay(2);
    }
  }

  delay(5);

  printf("\nparent: freezing child pid %d\n", pid);

  if(freeze(pid) < 0){
    printf("parent: freeze failed\n");
    kill(pid);
    wait(0);
    exit(1);
  }

  printf("parent: child is frozen now...\n");

  
  delay(200);

  printf("\nparent: unfreezing child pid %d\n", pid);

  if(unfreeze(pid) < 0){
    printf("parent: unfreeze failed\n");
    kill(pid);
    wait(0);
    exit(1);
  }

  printf("parent: child is unfrozen now. Child output should return...\n");
  delay(10);

  kill(pid);
  wait(0);

  printf("\nfreezertest done\n");
  exit(0);
}
