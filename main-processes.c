#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc,  char* argv[]) {
    int x = 10;
    int pid = fork();
    if(pid == -1){
        return 1;
    }

    if (pid == 0){
        // Inside the child proces
        x++;
    }
    sleep(2);
    printf("process id : %d   forkreturn pid: %d  value of x : %d\n", getpid(), pid, x);
    // printf("hello from process\n");
    // printf("process id is %d\n", getpid());

    if(pid != 0){
        wait(NULL);
    }
    return 0;
}