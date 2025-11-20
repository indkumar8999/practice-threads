#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 8

int count = 0;
pthread_mutex_t mutex;

void* routine(void* args){
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    // Now we can lock it again but we need to unlock it the same number of times we lock it 
    // Other wise we will have other threads still waiting on this mutex
    // THIS IS APPLICABLE ONLY ON ONE THREAD AND IS NOT THE SAME AS SEMAPHORE
    count += 5;
    printf("increased count by 5; vallue now : %d\n", count);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    return NULL;
}


int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t threads[THREAD_NUM];

    pthread_mutexattr_t recursive_mutex_attributes;
    pthread_mutexattr_init(&recursive_mutex_attributes);
    pthread_mutexattr_settype(&recursive_mutex_attributes, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &recursive_mutex_attributes);

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


    pthread_mutexattr_destroy(&recursive_mutex_attributes);
    pthread_mutex_destroy(&mutex);

    return 0;
}