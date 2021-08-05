#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[]){
    if(argc==0){
        exit(-1);
    }
    int n = atoi(argv[1]);
    sleep(n);
    exit(0);
}