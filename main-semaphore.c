#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 8

sem_t sem;

/*
For some reason this is working as expected in linux env, they are waiting a second and then printing
but on MAC, all of the threads are printing at the same time
*/

void* routine(void* args){
    sem_wait(&sem);
    sleep(1);
    printf("i am thread %d\n", *(int*)args);
    sem_post(&sem);
    free(args);
    return NULL;
}

int main(int argc, char* argv[]){
    // srand(time(NULL));
    pthread_t threads[THREAD_NUM];

    // The second argument is used to indicte if this semaphore is shared across multiple processes
    // If we are using this sempahore in just one process and the threads in that process
    // share it then set to 0 if not then set to non-zero value
    sem_init(&sem, 0, 1);

    for(int i=0;i<THREAD_NUM;i++){
        int* k = malloc(sizeof(int));
        *k = i;
        if(pthread_create(threads+i, NULL, &routine, k) != 0){
            perror("error creating threads");
        }
    }

    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("error joining threads");
        }
    }

    sem_destroy(&sem);
    return 0;
}