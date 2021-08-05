#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int p1[2];  // p1[0]: read fd, p1[1]: write fd
    int p2[2];
    char buf;
    int n;

    pipe(p1);
    pipe(p2);

    if(fork()==0){ // child
        write(p1[1], &buf, 1);
        n = read(p2[0], &buf, 1);
        if(n==1){
            printf("%d: received pong\n", getpid());
            exit(0);
        }
        else{
            exit(-1);
        }
    }    
    else{ // parent
        n = read(p1[0], &buf, 1);
        if(n==1){
            printf("%d: received ping\n", getpid());
            write(p2[1], &buf, 1);
            wait((int*)0); 
            exit(0);
        }
        else{
            exit(-1);
        }
    }

}
