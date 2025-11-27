#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    int arr[] = {1,2,3,4,4,3,5,6,3,5,1};
    int arrSize = sizeof(arr)/sizeof(int);
    int fd[2];
    int start, end;
    if(pipe(fd) == -1){
        printf("error creating pipe");
        return 2;
    }
    int id = fork();
    if(id == -1){
        return 2;
    }

    if (id == 0){
        start = 0;
        end = arrSize/2;
    }else {
        start = arrSize/2;
        end = arrSize;
    }


    int sum = 0;
    for(int i=start;i<end;i++){
        sum += arr[i];
    }

    printf("partial sum is : %d\n", sum);
    if(id == 0){
        write(fd[1], &sum, sizeof(int));
        close(fd[1]);
        close(fd[0]);
    } else {
        close(fd[1]);
        int childSum;
        read(fd[0], &childSum, sizeof(int));
        close(fd[0]);

        printf("total sum is :%d\n", childSum + sum);
        wait(NULL); // wait for child to finish
    }

    return 0;
}