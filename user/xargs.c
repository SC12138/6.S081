#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main (int argc, char* argv[]){
    char* exec_argv[MAXARG];
    // int exec_argc = 1;
    for(int i=0; i<argc-1; i++){
        exec_argv[i] = argv[i+1];
    }
    // last arg in exec_argv should be in exec_argv[argc-1]
    char buf[512];
    int p=0;

    while(read(0, &buf[p], 1)!=0){
        if(buf[p]!='\n'){
            p++;
            continue;
        }
        buf[p] = '\0';
        exec_argv[argc-1] = buf;
        if(fork()==0){ // child
            // printf(argv[0]);
            exec(argv[1], exec_argv);
        }
        else{ // parent
            p = 0;
            wait((int*)0);
        }
    }
    exit(0);
    
}