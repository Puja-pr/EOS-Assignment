#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>

#define SEM_KEY 0x4321

union semun 
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

void sigchld_handler(int sig) 
{
    int s;
    waitpid(-1, &s, 0);
}

int main() 
{
    int ret, semid;
    struct sigaction sa;
    union semun su;
    struct sembuf ops[1];

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigchld_handler;
    sigaction(SIGCHLD, &sa, NULL);

    semid = semget(SEM_KEY, 2, IPC_CREAT | 0600);
    
    su.val = 1;
	semctl(semid, 0, SETVAL, su);
    su.val = 0;
	semctl(semid, 1, SETVAL, su);

    ret = fork();
    
    if (ret == 0) 
	{ 
		char *str = "INFOTECH\n";
        while (1) 
		{
        	ops[0].sem_num = 1; 
            ops[0].sem_op = -1;
            ops[0].sem_flg = 0;
            
            ops[1].sem_num = 1; 
            ops[1].sem_op = -1;
            ops[1].sem_flg = 0;
            semop(semid, ops, 2);

            for(int i=0; str[i]!='\0'; i++) 
			{
            	write(1, &str[i], 1);
				sleep(1);
        	} 

			ops[0].sem_num = 0;
            ops[0].sem_op = +1;
            ops[0].sem_flg = 0;
            semop(semid, ops, 1);
  
        }
        _exit(0);
    } 
	else 
	{ 
		char *str = "SUNBEAM\n";
        while (1) 
		{ 
            ops[0].sem_num = 0; 
            ops[0].sem_op = -1;
            ops[0].sem_flg = 0;
            semop(semid, ops, 1);
            
            for(int i=0; str[i]!='\0'; i++) 
			{
            	write(1, &str[i], 1);
				sleep(1);
        	} 

			ops[0].sem_num = 1; 
            ops[0].sem_op = +1;
            ops[0].sem_flg = 0;

		 	ops[1].sem_num = 1; 
            ops[1].sem_op = +1;
            ops[1].sem_flg = 0;
            semop(semid, ops, 2);
        }

        semctl(semid, 0, IPC_RMID); 
    }
    
    return 0;
}
