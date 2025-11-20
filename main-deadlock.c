#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 8

int count = 0;
pthread_mutex_t mutex;

int other = 0;
pthread_mutex_t mutex2;


/*
void* routine(void* args){
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    // This also causes DEADLOCK even if the same thread has already obtained the lock
    // because pthread here will just try to get the lock again

    count += 5;
    other = count;

    printf("increased count by 5; vallue now : %d\n", count);
    pthread_mutex_unlock(&mutex);

    return NULL;
}
*/


void* routine(void* args){
    // Simulating different locking order with rand
    if(rand()%2 == 0){
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex);
    }else{
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex2);
    }
    
    // This also causes DEADLOCK even if the same thread has already obtained the lock
    // because pthread here will just try to get the lock again

    count += 5;
    other = count;

    printf("increased count by 5; vallue now : %d\n", count);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t threads[THREAD_NUM];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);

    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_create(threads+i, NULL, &routine, NULL) != 0){
            perror("error creating threads");
        }
    }


    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("error joining threads");
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);

    return 0;
}