#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pid;
    int p[2];
    
    pipe(p);
    if(fork()==0){
        pid=getpid();
        char buf[2];
        if(read(p[0],buf,1)!=1){
            fprintf(2,"failed to read in child  ");
            exit(1);
        }
        close(p[0]);
        printf("%d: received ping\n",pid);
        if(write(p[1],buf,1)!=1){
            fprintf(2,"failed to write in child");
            exit(1);
        }
        close(p[1]);
        exit(0);
    }
    else {
        pid=getpid();
        char info[2]="a";
        char buf[2];
        if(write(p[1],info,1)!=1){
            fprintf(2,"failed to write in parent");
            exit(1);
        }
        close(p[1]);
        wait(0);
        if(read(p[0],buf,1)!=1){
            fprintf(2,"failed to read in parent");
            exit(1);
        }
        close(p[0]);
        printf("%d: received pong\n", pid);
        exit(0);
    }





/*    if(pid>0)
    {
        close(1);
        dup(p[1]);
        read(p[1],buf,8);
        int get_pid=getpid();
        fprintf(1,"%d: received ping");




        close(0);
        dup(p[0]);
        write(p[0],"12345678",8);
        int get_pid=getpid();
        fprintf(1,"%d: received ping");
    }
*/

}