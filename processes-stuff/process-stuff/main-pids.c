#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int id = fork();

    if(id == 0){
        sleep(1);
    }

    printf("process id : %d\n", getpid());
    printf("parent id : %d\n", getppid());

    int res = wait(NULL); //returns process id of the child that is finished, returns -1 if no child process.
    if(res == -1){
        printf("no children to wait for \n");
    }else {
        printf("%d finished execution\n", res);
    }

    return 0;
}

/*
If a parent process is termintated before child process then the child process is automatically assigned a parent process.
All of the processes in the system will have a parent process except the first process 

And such child process are not going to be terminated with signals and can cause a memory leak because
that memory is not freed 

A best practice would be to wait for child process to finish and then terminate parent
*/