#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include"kernel/param.h"

int readline(int new_argc,char* new_argv[]){
    char buf[1024];
    int n=0;
    while(read(0,buf+n,1)){
      if(n==1023){
        fprintf(2,"argument is too long\n");
        exit(1);
      }
      if(buf[n]=='\n')
        break;
      n++;
    }
    buf[n]=0;

    if(n==0)
  return 0;
  int offest=0;
  while(offest<n){
    new_argv[new_argc++]=buf+offest;
    while(buf[offest]!=' '&&offest<n)
      offest++;
    while(buf[offest]==' '&&offest<n)
      buf[offest++]=0;
  }
  
  return new_argc;
}


int main(int argc,char* argv[]){

	if (argc <= 1)
	{
		fprintf(2, "Usage: xargs command (arg ...)\n");
		exit(1);
	}

  char * command =malloc(strlen(argv[1]) + 1);
  strcpy(command,argv[1]);
  char * new_argv[MAXARG];
  for(int i=1; i<argc; i++){
    new_argv[i-1]=(char *)malloc(strlen(argv[i])+1);
    strcpy(new_argv[i-1],argv[i]);
  }
    int new_argc;
    while((new_argc=readline(argc-1,new_argv))!=0){
        new_argv[new_argc] = 0;
        if(fork()==0){
          exec(command,new_argv);
          fprintf(2, "exec failed\n");
			    exit(1);
        }
      wait(0);
    }
    
exit(0);
}