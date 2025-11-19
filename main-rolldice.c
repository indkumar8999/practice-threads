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

    // Returning a local variable reference will cause seg fault
    // because it would be deallocated
    // So we need to allocate memory dynamicaly

    // And we can type case int* to void* in c.

    printf("result pointer in thread : %p\n", result);
    printf("result in thread : %d\n", *result);

    return (void*) result;
}


int main(int argc, char* argv[]){
    pthread_t thread;
    srand(time(NULL));

    int* result;

    if(pthread_create(&thread, NULL, &routine, NULL) != 0){
        return 1;
    }

    if(pthread_join(thread, (void**) &result) != 0){
        return 2;
    }

    printf("result pointer : %p\n", result);
    printf("result : %d\n", *result);

    // Once we are done with using result
    // We need to de allocate result

    free(result);

    // THIS IS A BAD DESIGN SINCE WE ARE DEALLOCATING A VARIABLE THAT IS
    // DEFINED IN ANOTHER FUNCTION AND IS DEALLOCATED IN main
    // THIS IS BAD

    return 0;
}