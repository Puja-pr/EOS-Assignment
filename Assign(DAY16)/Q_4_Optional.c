//Implement producer consumer across two processes using POSIX semaphores and Mutexes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>

#define SIZE 5

typedef struct 
{
    int arr[SIZE];
    int front, rear, count;
} cirque_t;

cirque_t *cq;
sem_t *empty;
sem_t *full;
pthread_mutex_t *mutex;

void cq_init(cirque_t *cq) 
{
    memset(cq->arr, 0, sizeof(cq->arr));
    cq->count = 0;
    cq->front = 0;
    cq->rear = 0;
}

int cq_isfull(cirque_t *cq) 
{
    return cq->count == SIZE;
}

int cq_isempty(cirque_t *cq) 
{
    return cq->count == 0;
}

void cq_push(cirque_t *cq, int val) 
{
    cq->arr[cq->rear] = val;
    cq->rear = (cq->rear + 1) % SIZE;
    cq->count++;
}

int cq_pop(cirque_t *cq) 
{
    int val = cq->arr[cq->front];
    cq->front = (cq->front + 1) % SIZE;
    cq->count--;
    return val;
}

void cleanup() 
{
    munmap(cq, sizeof(cirque_t));
    sem_destroy(empty);
    sem_destroy(full);
    pthread_mutex_destroy(mutex);
}

void sigint_handler(int sig)
{
    cleanup();
    exit(0);
}

void* producer(void* arg) 
{
    while(1) 
	{
        int val = rand() % 100;
        sem_wait(empty);
        pthread_mutex_lock(mutex);
        cq_push(cq, val);
        printf("WR: %d\n", val);
        pthread_mutex_unlock(mutex);
        sem_post(full);
        sleep(1);
    }
}

void* consumer(void* arg) 
{
    while(1) 
	{
        sem_wait(full);
        pthread_mutex_lock(mutex);
        int val = cq_pop(cq);
        printf("RD: %d\n", val);
        pthread_mutex_unlock(mutex);
        sem_post(empty);
        sleep(1);
    }
}

int main() 
{
    signal(SIGINT, sigint_handler);
    int shm_size = sizeof(cirque_t);
    cq = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    cq_init(cq);

    empty = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    full = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    mutex = mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(empty, 1, SIZE); 
	sem_init(full, 1, 0);      
	pthread_mutexattr_t attr;
    
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    
    pthread_mutex_init(mutex, &attr);

    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    cleanup(); 

	return 0;
}
