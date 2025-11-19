#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t fuel_cond;

void* fuel_filling(void* arg) { 
    for(int i=0;i<5;i++){
        pthread_mutex_lock(&fuel_mutex);
        fuel += 20;
        printf("filling fuel, Now it is %d \n", fuel);
        pthread_mutex_unlock(&fuel_mutex);
        // pthread_cond_signal(&fuel_cond);
        // pthread_cond_signal only signals one car but not all of them
        // so only one of them checks the fuel but not all of them

        pthread_cond_broadcast(&fuel_cond);
        // pthread_cond_broadcast will signals all of the threads and each of them will check
        // the condition and decreases fuel if only they get a lock.
        sleep(1);
    }
}


void* car(void* arg){
    pthread_mutex_lock(&fuel_mutex);
    while(fuel < 40){
        printf("no fuel. Waiting..\n");
        pthread_cond_wait(&fuel_cond, &fuel_mutex);

        // The pthread_cond_wait is equivalent to 
        // pthread_mutex_unlock(&fuel_mutex);
        // Wait for signal
        // pthread_mutex_lock(&fuel_mutex);
    }

    fuel -= 40;
    printf("got fuel. Now remaining fuel %d\n", fuel);
    pthread_mutex_unlock(&fuel_mutex);
}

int main(int argc, char* argv[]) {
    int n = 10;

    pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&fuel_cond, NULL);
    pthread_t threads[n];
    for(int i=0;i<n;i++){
        if(i == 0 || i == 4){ 
            if(pthread_create(threads+i, NULL, &fuel_filling, NULL) != 0){
                return 2;
            }
        }else {
            if(pthread_create(threads+i, NULL, &car, NULL) != 0){
                return 2;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(pthread_join(threads[i], NULL) != 0){
            return 2;
        }
    }
    pthread_mutex_destroy(&fuel_mutex);
    pthread_cond_destroy(&fuel_cond);
    return 0;
}