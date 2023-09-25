#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int num;
  char *numbers;

  if(argc <= 1){
    fprintf(2, "usage: sleep numbers\n");
    exit(1);
  }
  numbers = argv[1];

  if(argc == 2){
    num =  atoi(numbers);
    sleep(num);
    
    exit(0);
  }
  exit(0);
}