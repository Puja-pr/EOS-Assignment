#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct input 
{
    int start;
    int end;
};

struct output 
{
	int sum;
    int err;
};

void* sum(void *param) 
{
    struct input *ip = (struct input *)param;
    struct output *op = (struct output *)malloc(sizeof(struct output));
    op->sum = 0;

	if(ip->end < ip->start) 
	{
        printf("SUM : ERROR !\n");
        op->err = 1;
        pthread_exit(op);
    }
    
	for(int i = ip->start ; i <= ip->end ; i++)
	{
		op->sum = op->sum + i;
	}

	op->err = 0;
	pthread_exit(op);

	return op;
}

int main() 
{
	int ret;
    pthread_t th;
    struct input in;
    struct output *out;

	printf("Enter the START of range : ");
	scanf("%d",&in.start);
	printf("Enter the END of range : ");
	scanf("%d",&in.end);
    ret = pthread_create(&th , NULL , sum , &in);
 	pthread_join(th, (void**)&out);
    
	if(out->err == 0) 
	{
		printf("MAIN : SUM = %d\n",out->sum);
    }
	else
	{

		printf("MAIN : Range Is Invalid !\n");
	}

	free(out);
    return 0;
}
