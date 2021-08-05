#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"

int checker(char* path, char* dest){
    int fd;
    struct dirent de;
    struct stat st;
    char buf[512];
    char *p;
    

    if((fd=open(path, O_RDONLY))<0){
        printf("find: can't open path %s", path);
        return -1;
    }
    while(read(fd, &de, sizeof(de))){
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if(de.inum == 0){
            continue;
        }
        if(stat(buf, &st)<0){
            return -1;
        }
        if((st.type!=T_DIR) && (strcmp(de.name, dest)==0)){
            printf("%s\n", buf);
        }
        else if((st.type==T_DIR)&&(strcmp(de.name, ".")!=0)&&(strcmp(de.name, "..")!=0)){
            checker(buf, dest);
        }
    }
    return 0;
}

void main (int argc, char* argv[]){
    if(argc!=3){
        exit(-1);
    }
    if (checker(argv[1], argv[2])<0){
        printf("error");
    }
    exit(0);
}