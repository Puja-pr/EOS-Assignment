// One thread prints "SUNBEAM" continuously, and other thread prints "INFOTECH" continhously. Only one should print at a time starting with "SUNBEAM". Hint: using condition variables

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;
pthread_cond_t c;
int turn = 0;

void* sunbeam(void *param) 
{
    char *str = "SUNBEAM\n";
    
	while (1) 
	{
        pthread_mutex_lock(&m);
        
		while (turn != 0) 
		{ 
            pthread_cond_wait(&c, &m);
        }

        for (int i = 0; str[i] != '\0'; i++) 
		{
            write(1, &str[i], 1);
            sleep(1); 
        }

        turn = 1;
        pthread_cond_signal(&c); 
        pthread_mutex_unlock(&m);
    }

    return NULL;
}

void* infotech(void *param) 
{
    char *str = "INFOTECH\n";
    
	while (1) 
	{
        pthread_mutex_lock(&m);
        
		while (turn != 1) 
		{ 
            pthread_cond_wait(&c, &m);
        }

        for (int i = 0; str[i] != '\0'; i++)
		{
            write(1, &str[i], 1);
            sleep(1);
        }
        
		turn = 0; 
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
    }

    return NULL;
}

int main() 
{

printf("Press enter to exit...\n");
    pthread_t st, it;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);
    pthread_create(&st, NULL, sunbeam, NULL);
    pthread_create(&it, NULL, infotech, NULL);

    pthread_mutex_lock(&m);
    turn = 0; 
    pthread_cond_signal(&c); 
    pthread_mutex_unlock(&m);

    getchar(); 
    pthread_cancel(st);
    pthread_cancel(it);
    
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);

    return 0;
}
