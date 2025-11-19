#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mu;

void* routine(){
    for(int i=0;i<100000;i++){
        pthread_mutex_lock(&mu);
        count++;
        pthread_mutex_unlock(&mu);
    }
}

int main(int argc, char* argv[]){
    int n=5;

    pthread_t threads[n];
    pthread_mutex_init(&mu, NULL);
    int i;
    for(i=0;i<n;i++){
        // Point to remember: pthread_create takes thread address as input
        // Whereas pthread_join takes the thread instance as input
        if(pthread_create(threads+i, NULL, &routine, NULL) != 0){
            return 1;
        }
        printf("thread %d has started \n", i);
    }

    for(int i=0;i<n;i++){
        // Pthread join is a blocking call and waits until thread1 stop and then only proceeds to
        // join for thread2 and so on...

        // Even if the threads finished in a different order, we are joining for them in the increasing order of index.
        if(pthread_join(threads[i], NULL) != 0){
            return 1;
        }
        printf("thread %d has finished \n", i);
    }

    pthread_mutex_destroy(&mu);
    printf("count value: %d\n", count);
    return 0;
}