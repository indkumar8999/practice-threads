#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/syscall.h>

/* The system call below only works on linux, It doesn't work on mac
The pthread_self will return the id but not the SYS_gettid.


pthread_self id value is maintained by the pthread api
SYS_gettid is managed by the Operating system and is different from the pthread_self id

Our program -> pthread api -> OS thread

*/

void* routine(void* arg) {
    pthread_t th = pthread_self();
    printf("pthread_t printed as unsigned long: %ul \n", th);

    printf("syscall thread id: %d \n", (pid_t)syscall(SYS_gettid));
}

int main(int argc, char* argv[]){
    int n = 2;
    pthread_t threads[n];

    for(int i=0;i<n;i++){
        if(pthread_create(threads+i, NULL, &routine, NULL) != 0){
            return 1;
        }
    }

    for(int i=0;i<n;i++){
        if(pthread_join(threads[i], NULL) != 0){
            return 1;
        }
    }
    return 0;
}