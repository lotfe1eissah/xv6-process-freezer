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
  int child1;
  int child2;

  printf("freezer multi-process test started\n");

  child1 = fork();

  if(child1 < 0){
    printf("fork child1 failed\n");
    exit(1);
  }

  if(child1 == 0){
    int i = 0;
    while(1){
      printf("child1 running %d\n", i++);
      delay(2);
    }
  }

  child2 = fork();

  if(child2 < 0){
    printf("fork child2 failed\n");
    kill(child1);
    wait(0);
    exit(1);
  }

  if(child2 == 0){
    int i = 0;
    while(1){
      printf("child2 running %d\n", i++);
      delay(2);
    }
  }

  delay(8);

  printf("\nparent: freezing child1 pid %d\n", child1);

  if(freeze(child1) < 0){
    printf("parent: freeze child1 failed\n");
    kill(child1);
    kill(child2);
    wait(0);
    wait(0);
    exit(1);
  }

  printf("parent: child1 should stop, but child2 should keep running\n");
  delay(25);

  printf("\nparent: unfreezing child1 pid %d\n", child1);

  if(unfreeze(child1) < 0){
    printf("parent: unfreeze child1 failed\n");
    kill(child1);
    kill(child2);
    wait(0);
    wait(0);
    exit(1);
  }

  printf("parent: both children should run again\n");
  delay(12);

  kill(child1);
  kill(child2);
  wait(0);
  wait(0);

  printf("\nfreezer multi-process test done\n");
  exit(0);
}
