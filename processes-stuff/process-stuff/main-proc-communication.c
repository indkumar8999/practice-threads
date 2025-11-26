#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]){

    int fd[2];  // Write to fd[1] and read from fd[0]

    // Pipe takes 2 file descriptors say f0, f1
    // The data[bytes] that is written on to f1 will be accessable to read from f0
    if(pipe(fd) == -1){
        printf("erorr opening pipe \n");
        return 1;
    }

    int id = fork();

    if(id == -1){
        printf("error creating process with fork\n");
        return 4;
    }

    if(id == 0){
        // child process code
        int x;
        printf("input a number \n");
        scanf("%d", &x);

        if(write(fd[1], &x, sizeof(int)) == -1){
            printf("error writing to fd\n");
            return 2;
        }
        close(fd[1]); // Clsoe the file descriptor once we are done with writing the data
        close(fd[0]); // Close the read end as well since the file descriptors are copied over during process creation
    } else {
        // parent process code
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            printf("error reading the data from fd\n");
            return 3;
        }

        printf("read from the pipe file descriptor %d\n", y);
        close(fd[0]);
        close(fd[1]);
    }


    return 0;
}
