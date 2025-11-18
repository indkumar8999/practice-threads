#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void* routine() {
    x++;
    sleep(2);
    printf("value of x: %d\n", x);
}


void* routine2() {
    sleep(2);
    printf("value of x: %d\n", x);
}

int main(int argc, char* argv[]) {
    pthread_t thread1, thread2;
    if(pthread_create(&thread1, NULL, &routine, NULL) != 0){
        return 1;
    }

    if(pthread_create(&thread2, NULL, &routine2, NULL) != 0){
        return 2;
    }
    
    if(pthread_join(thread1, NULL) != 0){
        return 3;
    }
    if(pthread_join(thread2, NULL) != 0){
        return 4;
    }
    return 0;
}