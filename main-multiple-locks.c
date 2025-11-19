#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t stove_mutex[4];
int stove_fuel[4] = {100, 100, 100, 100};

void* routine(void* arg) {
    for(int i=0;i<4;i++){
        if(pthread_mutex_trylock(&stove_mutex[i]) == 0){
            int fuel_needed = rand()%30;
            if(stove_fuel[i] < fuel_needed) {
                printf("no more fuel, going home ..\n");
            }else {
                stove_fuel[i] -= fuel_needed;
                usleep(500000);
                printf("fuel left in stove %d is %d \n", i, stove_fuel[i]);
            }
            pthread_mutex_unlock(&stove_mutex[i]);
            break;
        } else {
            if(i == 3){
                printf("stoves busy trying in sometime\n");
                usleep(300000);
                i = 0;
            }else {
                printf("stove busy, checking next\n");
            }
        }
    }
    
}

int main(int argc, char* argv[]){
    pthread_t threads[10];
    srand(time(NULL));

    for(int i=0;i<4;i++){
        pthread_mutex_init(&stove_mutex[i], NULL); 
    }

    for(int i=0;i<10;i++){
        if(pthread_create(threads+i, NULL, *routine, NULL) != 0){
            return 1;
        }
    }

    for(int i=0;i<10;i++){
        if(pthread_join(threads[i], NULL) != 0){
            return 1;
        }
    }

    for(int i=0;i<4;i++){
        pthread_mutex_destroy(&stove_mutex[i]);
    }
    
    return 0;
}