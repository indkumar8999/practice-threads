#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>



/*

-> dice roll|(barrier) status update -> |(barrier_after_status_update)| rest of prints
*/



#define THREAD_NUM 8

int dice_values[THREAD_NUM];

int status[THREAD_NUM];

// IS NOT SUPPORTED ON MAC
pthread_barrier_t barrier, barrier_after_status_update;

void*  routine(void* arg){
	int index = *(int*)arg;

	

	dice_values[index] = rand()%6 + 1;
	
	pthread_barrier_wait(&barrier);

	pthread_barrier_wait(&barrier_after_status_update);
	if(status[index] == 1){
		printf("(%d) rolled (%d) and I won\n", index, dice_values[index]);
	}else{
		printf("(%d) rolled (%d) and lost\n", index, dice_values[index]);
	}

	free(arg);
}	

int main(int argc, char* argv[]){
	srand(time(NULL));
	pthread_barrier_init(&barrier, NULL, THREAD_NUM+1);
	pthread_barrier_init(&barrier_after_status_update, NULL, THREAD_NUM+1);

	// The number fo threads is THREAD_NUM+1 because we are waiting for all of the dice threads to roll the dice
	// And also once the dices are rolled for all of the child threads the main thread should also be present at the barrier
	// So that it can process all of the dice rolls.

	pthread_t threads[THREAD_NUM];

	for(int i=0;i<THREAD_NUM;i++){
		int* k = malloc(sizeof(int));
		*k = i;
		if(pthread_create(threads+i, NULL, &routine, (void*)k) != 0){
			return 1;
		}
	}
	
	pthread_barrier_wait(&barrier);

	int max = 0;
	for(int i=0;i<THREAD_NUM;i++){
		if(dice_values[i] > max){
			max = dice_values[i];
		}
	}


	for(int i=0;i<THREAD_NUM;i++){
                if(dice_values[i] == max){
                       	status[i] = 1;
                }else{
			status[i] = 0;
		}
        }
	pthread_barrier_wait(&barrier_after_status_update);
	for(int i=0;i<THREAD_NUM;i++){
                if(pthread_join(threads[i], NULL) != 0){
                        return 1;
                }
        }

	pthread_barrier_destroy(&barrier);
	pthread_barrier_destroy(&barrier_after_status_update);
	return 0;
}
