#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int id1 = fork();
    int id2 = fork();

    printf("process id %d, id1: %d id2 :%d \n", getpid(), id1, id2);


    while(wait(NULL) != -1 || errno != ECHILD){

        // We are waiting for all of the children to finish
        printf("waiting for child to finish\n");
    }
    return 0;
}
