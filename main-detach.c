#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/syscall.h>


void* routine(void* arg) {
    sleep(1);
    printf("in thread\n");
}

int main(int argc, char* argv[]){
    int n = 2;
    pthread_t threads[n];

    pthread_attr_t detached_thread;

    pthread_attr_init(&detached_thread);
    pthread_attr_setdetachstate(&detached_thread, PTHREAD_CREATE_DETACHED);
    for(int i=0;i<n;i++){
        if(pthread_create(threads+i, &detached_thread, &routine, NULL) != 0){
            return 1;
        }
        pthread_detach(threads[i]);
    }

    

    // for(int i=0;i<n;i++){
    //     // This gives an error
    //     if(pthread_join(threads[i], NULL) != 0){
    //         perror("failed to join thread");
    //     }
    // }

    // pthread_exit from the main thread instead of exit or return because we want to run the detached threads
    // in the background

    pthread_attr_destroy(&detached_thread);
    pthread_exit(0);
}