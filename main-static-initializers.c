#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/syscall.h>


// We can use this instread of pthread_mutex_init and pthread_mutex_destroy

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;

// Same as above
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void* routine(void* arg) {
    pthread_mutex_lock(&mu);
    printf("got lock in thread\n");
    pthread_mutex_unlock(&mu);
}

int main(int argc, char* argv[]){
    int n = 2;
    pthread_t threads[n];

    for(int i=0;i<n;i++){
        if(pthread_create(threads+i, NULL, &routine, NULL) != 0){
            return 1;
        }
    }

    for(int i=0;i<n;i++){
        if(pthread_join(threads[i], NULL) != 0){
            return 1;
        }
    }

    return 0;
}