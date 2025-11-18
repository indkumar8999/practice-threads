#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;



void* routine() {
    for(int i=0;i<100000;i++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);

    if(pthread_create(&thread1, NULL, &routine, NULL) != 0){
        return 1;
    }

    if(pthread_create(&thread2, NULL, &routine, NULL) != 0){
        return 2;
    }
    
    if(pthread_join(thread1, NULL) != 0){
        return 3;
    }
    if(pthread_join(thread2, NULL) != 0){
        return 4;
    }
    printf("count : %d", count);
    pthread_mutex_destroy(&mutex);
    return 0;
}