#include "kernel/types.h"
#include "user/user.h"

void
redirect(int k, int pd[])
{
  // dups the read/write end onto the file decriptor 0/1
  close(k);
  dup(pd[k]);
  // close the file descriptors in "pd"
  close(pd[0]);
  close(pd[1]);
}

int main (int argc, char *argv[]){
    int n = 2;
    int p[2];
    pipe(p);

    if(fork()==0){ // process 0
        // first prime 
        printf("prime %d\n", 2);
        redirect(1, p);
        for(int i=3; i<=35; i++){
            write(1, &i, 4);
        }
        close(1);
        wait((int *) 0);
        exit(0);
    }
    else{ // process 1
        int isLast = 1;
        int buf;
        int p2[2];
        redirect(0, p);
        while(read(0, &buf, 4)){
            if(buf%n==0){
                continue;
            }
            else{
                if(isLast==1){ // last process
                    pipe(p2);
                    if(fork()==0){ // parent
                        isLast = 0;
                        redirect(1, p2);
                        write(1, &buf, 4);
                    }
                    else{ // child
                        isLast = 1;
                        redirect(0, p2);
                        read(0, &buf, 4);
                        printf("prime %d\n", buf);
                        n = buf;
                    }   
                }
                else{
                    write(1, &buf, 4);
                }
            }
        }
        if(isLast==0){
            close(1);
            wait((int *) 0);
        }
        exit(0);
    }
}