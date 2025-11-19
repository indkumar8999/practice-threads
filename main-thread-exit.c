#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* routine(){
    int value = (rand()%6) + 1;
    printf("roll of dice is : %d \n", value);

    int* result = malloc(sizeof(int));

    *result =value;
    printf("result pointer in thread : %p\n", result);
    printf("result in thread : %d\n", *result);

    pthread_exit((void*) result);

    // pthread_exit can be used instead of return here to return the result from this thread
}


int main(int argc, char* argv[]){
    pthread_t thread;
    srand(time(NULL));

    int* result;

    if(pthread_create(&thread, NULL, &routine, NULL) != 0){
        return 1;
    }

    pthread_exit(0);
    // This pthread_exit will return from the main thread but will not terminate the process like exit(0) or return 0 does
    // Instead it will wait until all of the child threads finish their execution and then the process terminates

    // For this example though it is bad because we are not freeing the memory we have allocated in the routine function above
    // and that causes a memory leak

    if(pthread_join(thread, (void**) &result) != 0){
        return 2;
    }

    printf("result pointer : %p\n", result);
    printf("result : %d\n", *result);

    free(result);

    return 0;
}