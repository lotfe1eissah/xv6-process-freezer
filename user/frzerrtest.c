#include "kernel/types.h"
#include "user/user.h"

void
check(char *name, int result, int expected)
{
  if(result == expected){
    printf("[PASS] %s\n", name);
  } else {
    printf("[FAIL] %s: got %d expected %d\n", name, result, expected);
  }
}

void
delay(int n)
{
  volatile int i;
  for(i = 0; i < n * 3000000; i++){
  }
}

int
main(int argc, char *argv[])
{
  int pid;

  printf("freezer error test started\n");

  check("freeze invalid pid", freeze(-1), -1);
  check("unfreeze invalid pid", unfreeze(-1), -1);
  check("freeze init pid 1 should fail", freeze(1), -1);
  check("unfreeze init pid 1 should fail", unfreeze(1), -1);

  pid = fork();

  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){
    while(1){
      delay(1);
    }
  }

  delay(2);

  check("freeze child first time", freeze(pid), 0);
  check("freeze already frozen child", freeze(pid), -1);
  check("unfreeze child first time", unfreeze(pid), 0);
  check("unfreeze child not frozen", unfreeze(pid), -1);

  kill(pid);
  wait(0);

  printf("freezer error test done\n");
  exit(0);
}

