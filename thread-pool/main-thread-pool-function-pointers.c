#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 10

typedef struct Task {
    void (*taskFunction)(int, int); 
    int a, b;
} Task;

Task task_queue[256];
int task_count = 0;
pthread_mutex_t task_mutex;
pthread_cond_t task_cond;

void sumAndProduct(int a, int b) {
    printf("sum of %d, %d is %d \n", a, b, a+b);
    printf("prod of %d, %d is %d \n", a, b, a*b);
}


void execute_task(Task* task) {
    task->taskFunction(task->a, task->b);
}

void submit_task(Task task){
    pthread_mutex_lock(&task_mutex);
    task_queue[task_count] = task;
    task_count+=1;
    pthread_mutex_unlock(&task_mutex);
    pthread_cond_signal(&task_cond);
}

void* routine(void* args){
    while(1) {
        Task task;
        int found = 0;
        pthread_mutex_lock(&task_mutex);

        while(task_count == 0){
            pthread_cond_wait(&task_cond, &task_mutex);
        }
        if(task_count > 0){
            task = task_queue[0];
            found = 1;
    
            for(int i=0;i<task_count-1;i++){
                task_queue[i] = task_queue[i+1];
            }
            task_count -=1 ;
        }
        pthread_mutex_unlock(&task_mutex);
        if(found) {
            execute_task(&task);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t threads[THREAD_NUM];
    pthread_mutex_init(&task_mutex, NULL);
    pthread_cond_init(&task_cond, NULL);

    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_create(threads+i, NULL, &routine, NULL) != 0){
            perror("error creating threads");
        }
    }

    for(int i=0;i<100;i++){

        Task t = {
            .taskFunction = &sumAndProduct,
            .a = rand()%40+1,
            .b = rand()%4+1
        };
        submit_task(t);
    }

    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("error joining threads");
        }
    }

    pthread_mutex_destroy(&task_mutex);
    pthread_cond_destroy(&task_cond);

    return 0;
}