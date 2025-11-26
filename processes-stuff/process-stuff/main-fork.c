#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int id = fork();
    // if(id == 0){
    //     printf("child process : %d\n", id);
    // }else{
    //     printf("parent process : %d\n", id);
    // }
    // fork();
    // printf("hello\n");

    if(id == 0){
        //child process
    }else{
        id = fork();
    }

    
    if(id == 0){
        //child process
    }else{
        fork();
    }

    printf("process : %d\n", getpid());

    return 0;
}