#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 20

sem_t sem;

void* routine(void* args){
    printf("waiting in queue : thread %d\n", *(int*)args);
    sem_wait(&sem);
    printf("logged in : thread %d\n", *(int*)args);
    sleep(rand()%5+1);
    printf("logging out : thread %d\n", *(int*)args);
    sem_post(&sem);
    free(args);
    return NULL;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t threads[THREAD_NUM];

    sem_init(&sem, 0, 12);

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