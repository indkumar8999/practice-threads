#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int arr[100];

void* routine(void* arg) {
    int index = *(int*)arg;
    printf("%d \n", index);

    free(arg);
}


int main(int argc, char* argv[]) {

    for(int i=0;i<100;i++){
        arr[i] = 2*i;
    }

    pthread_t threads[10];
    for(int i=0;i<10;i++){
        int* k = malloc(sizeof(int));
        *k = i;
        if(pthread_create(threads+i, NULL, &routine, k) != 0) {
            printf("failed to created thread");
            return 2;
        }
    }

    for(int i=0;i<10;i++){
        if(pthread_join(threads[i], NULL) != 0) {
            return 2;
        }
    }
    return 0;
}