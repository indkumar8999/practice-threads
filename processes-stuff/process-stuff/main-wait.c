#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
    int id = fork();
    int n;

    if(id == 0){
        n = 1;
    }else{
        n = 6;
    }

    if(id != 0){
        wait(); // This waits for a child process
    }

    int i;
    for(i=n;i<n+5;i++){
        printf("%d\n", i);
        fflush(stdout); // Printing right way instead of waiting for print on console
        usleep(100);
    }

    return 0;
}