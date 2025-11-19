#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int arr[10];

void* routine(void* arg) {
    int index = *(int*)arg;
    int sum = 0;

    for(int i=0;i<5;i++){
        sum += arr[i+index];
    }
    *(int*)arg = sum; 
    return arg;
}


int main(int argc, char* argv[]) {

    for(int i=0;i<10;i++){
        arr[i] = 2*i;
    }

    pthread_t threads[2];
    for(int i=0;i<2;i++){
        int* k = malloc(sizeof(int));
        *k = i*5;
        if(pthread_create(threads+i, NULL, &routine, k) != 0) {
            printf("failed to created thread");
            return 2;
        }
    }
    int total_sum = 0;
    for(int i=0;i<2;i++){
        int* result;
        if(pthread_join(threads[i], (void*)&result) != 0) {
            return 2;
        }
        total_sum += *result;
        free(result);
    }

    printf("total sum:  %d\n", total_sum);
    return 0;
}