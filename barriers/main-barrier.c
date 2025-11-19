#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


/*

->  |
->  | Will let the threads enter if a certain number of threads reach the barrier.
    |
  barrier
*/

// IS NOT SUPPORTED ON MAC
pthread_barrier_t barrier;

void* routine(){
    printf("waiting at the barrier\n");
    pthread_barrier_wait(&barrier);
    printf("entered the barrier\n");
}


int main(int argc, char* argv[]){
    int n = 9;
    pthread_t threads[n];
    pthread_barrier_init(&barrier, NULL, 3);

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
    pthread_barrier_destroy(&barrier);
    return 0;
}
