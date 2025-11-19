#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mu;

void* routine() {
    // With trylock
    // If a thread doesn't get a lock it will not block
    // And it wil move forward to the else block and continue the execution
    if(pthread_mutex_trylock(&mu) == 0){
        printf("got lock\n");
        sleep(2);
        pthread_mutex_unlock(&mu);
    } else {
        printf("didn't get lock\n");
    }
}

int main(int argc, char* argv[]) {
    int n=4;
    pthread_t threads[n];
    pthread_mutex_init(&mu, NULL);
    int i;
    for(i=0;i<n;i++){
        if(pthread_create(threads+i, NULL, &routine, NULL) != 0){
            return 1;
        }
    }

    for(int i=0;i<n;i++){
        if(pthread_join(threads[i], NULL) != 0){
            return 1;
        }
    }

    pthread_mutex_destroy(&mu);
    return 0;
}