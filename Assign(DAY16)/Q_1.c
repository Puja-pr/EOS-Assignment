// Create a thread to sort given array of 10 integers using selection sort. Main thread should print the result after sorting is complete.

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* thread_func(void *param) 
{
    int *arr = (int*)param;
    
	for (int i = 0; i < 7 - 1; i++) 
	{
        int min_idx = i;
        
		for (int j = i + 1; j < 7; j++) 
		{
            if (arr[j] < arr[min_idx]) 
			{
                min_idx = j;
            }
        }

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }

    return NULL;
}

int main() 
{
    int ret, arr[7];
    printf("Enter %d integers:\n", 7);
    
	for (int i = 0; i < 7; i++) 
	{
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
	pthread_t th;
    pthread_create(&th, NULL, thread_func, (void*)arr);
    
	if(ret != 0)
	{
        perror("Pthread_create() failed!");
        return 1;
    }

    pthread_join(th, NULL);

    printf("Sorted array: ");
    
	for (int i = 0; i < 7; i++) 
	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
