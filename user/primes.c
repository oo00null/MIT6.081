#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void new_pocess(int p[2]){
    int prime;
    int n;
    int pnew[2];
    int read_val;
    close(p[1]);
    if((read_val=read(p[0],&prime,4))!=4){
        fprintf(2,"failed to read from pipe in PID: %d read_return value is %d\n",getpid(),read_val);
        exit(1);
    }
    printf("prime %d\n",prime);

    if(read(p[0],&n,4)){
        pipe(pnew);
        if(fork()==0){
            new_pocess(pnew);
        }
        else{
            close(pnew[0]);
            if(n%prime)write(pnew[1],&n,4);
            while(read(p[0],&n,4)){
                if(n%prime)write(pnew[1],&n,4);
            }
    
                close(p[0]);
                close(pnew[1]);
                wait(0);
            }
    }
    exit(0);
}


int main(int argc, char* argv[]){
    
    int p[2];
    pipe(p);

    if(fork()==0){
    new_pocess(p);
    }
    else{
        close(p[0]);
        for(int i=2;i<=35;i++){
            if(write(p[1],&i,4)!=4){
                fprintf(2,"first process failed %d into write in pipe\n",i);
                exit(1);
            }
        }
        close(p[1]);
        wait(0);
        exit(0);

    }
return 0;
}