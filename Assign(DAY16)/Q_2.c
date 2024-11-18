// Create a thread to sort given array of "n" integers using bubble sort. Main thread should print the result after sorting is completed. Pass struct address to thread function (via arg4 of pthread_create()).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct array 
{
    int *arr;
    int size;
};

void* bubble_sort(void* arg) 
{
    struct array* arr_struct = (struct array*)arg;
    int n = arr_struct->size;
    int* arr = arr_struct->arr;
    int temp;
    
	for (int i = 0; i < n - 1; i++) 
	{
        for (int j = 0; j < n - i - 1; j++) 
		{
            if (arr[j] > arr[j + 1]) 
			{
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    return NULL;
}

int main() 
{
    struct array arr_struct;
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    arr_struct.arr = (int*)malloc(n * sizeof(int));
    arr_struct.size = n;
    printf("Enter %d integers:\n", n);
    
	for (int i = 0; i < n; i++) 
	{
        scanf("%d", &arr_struct.arr[i]);
    }

    pthread_t th;
    pthread_create(&th, NULL, bubble_sort, (void*)&arr_struct);
    pthread_join(th, NULL);

    printf("Sorted array:\n");
    
	for (int i = 0; i < n; i++) 
	{
        printf("%d ", arr_struct.arr[i]);
    }
    free(arr_struct.arr);
    
    return 0;
}
