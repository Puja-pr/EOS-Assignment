#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 5

typedef struct cirque 
{
    int arr[SIZE];
    int front, rear, count;
}cirque_t;

void cq_init(cirque_t *cq) 
{
    memset(cq->arr, 0, sizeof(cq->arr));
    cq->count = 0;
    cq->front = -1;
    cq->rear = -1;
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
    cq->rear = (cq->rear + 1) % SIZE;
    cq->arr[cq->rear] = val;
    cq->count++;
}

int cq_pop(cirque_t *cq) 
{
    cq->front = (cq->front + 1) % SIZE;
    cq->count--;
    return cq->arr[cq->front];
}

#define SHM_KEY 0x1234

int shmid;
cirque_t *ptr;

void sigint_handler(int sig) 
{
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    _exit(0);
}

void sigchld_handler(int sig) 
{
    int s;
    waitpid(-1, &s, 0);
}

int main() 
{
    int pid, ret;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    ret = sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = sigchld_handler;
    ret = sigaction(SIGCHLD, &sa, NULL);
    
    shmid = shmget(SHM_KEY, sizeof(cirque_t), IPC_CREAT|0600);
    ptr = shmat(shmid, NULL, 0);
    cq_init(ptr);

    pid = fork();
    if(pid == 0) 
	{
        while(1) 
		{
            int val = cq_pop(ptr);
            printf("RD: %d\n", val);
            sleep(1);
        }
    }
    else
	{
        while(1) 
		{
            int val = rand() % 100;
            cq_push(ptr, val);
            printf("WR: %d\n", val);
            sleep(1);
        }
    }
    return 0;
}
