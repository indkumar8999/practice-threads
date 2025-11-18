#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine() {
    printf("in a routine \n");
    sleep(3);
    printf("exiting a routine \n");
}

int main(int argc, char* argv[]) {
    pthread_t thread1, thread2;
    if(pthread_create(&thread1, NULL, &routine, NULL) != 0){
        return 1;
    }

    if(pthread_create(&thread2, NULL, &routine, NULL) != 0){
        return 1;
    }

    // The error checks are done using the return int value form the pthread methods
    // If we get anything other than 0 then we have an error
    // This is possible in environments of linux when there are restrictions to create threads
    // And it is better to handle those scenarios in code
    
    if(pthread_join(thread1, NULL) != 0){
        return 1;
    }
    if(pthread_join(thread2, NULL) != 0){
        return 1;
    }
    return 0;
}