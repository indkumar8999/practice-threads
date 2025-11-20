#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define PRODS 10
#define CONS 10

int buffer[10];
int count = 0;

pthread_mutex_t mutex;

sem_t sem_empty;
sem_t sem_full;

void* producerfunction(void* args){

    while(1){
        // create random number
        int x= rand()%50;
        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex);
        // add to buffer
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_full);
    }
    return NULL;
}


void* consumerfunction(void* args){
    int k = -1;
    while(1){
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);
        k = buffer[count-1];
        count--;
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_empty);

        printf("consumer read: %d\n", k);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    sem_init(&sem_empty, 0, 10);
    sem_init(&sem_full, 0, 0);

    pthread_t producers[PRODS];
    for(int i=0;i<PRODS;i++){
        if(pthread_create(producers+i, NULL, &producerfunction, NULL) != 0) {
            perror("error creating producer thread.");
        }
    }

    pthread_t consumers[CONS];
    for(int i=0;i<CONS;i++){
        if(pthread_create(consumers+i, NULL, &consumerfunction, NULL) != 0) {
            perror("error creating consumer thread.");
        }
    }

    for(int i=0;i<PRODS;i++){
        if(pthread_join(producers[i], NULL) != 0){
            perror("error joining producer thread.");
        }
    }

    for(int i=0;i<CONS;i++){
        if(pthread_join(consumers[i], NULL) != 0){
            perror("error joining consumer thread.");
        }
    }

    pthread_mutex_destroy(&mutex);

    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    return 0;
}
