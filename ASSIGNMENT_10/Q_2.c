// The child process send two numbers to the parent process via pipe. The parent process calculate the sum and return via another pipe. The child process print the result and exit. The parent process wait for completion of the child and then exit.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    int pipe1[2];
    int pipe2[2];
    int pid, num1, num2, sum;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) 
	{
        perror("pipe");
        _exit(1);
    }

    pid = fork();
    
	if (pid < 0) 
	{
        perror("fork");
        _exit(1);
    }

    if (pid > 0) 
	{
        close(pipe1[0]);
        close(pipe2[1]);

        printf("Enter Num1 : ");
		scanf("%d",&num1);
		printf("Enter Num2 : ");
		scanf("%d",&num2);
		
        write(pipe1[1], &num1, sizeof(num1));
        write(pipe1[1], &num2, sizeof(num2));
        
        read(pipe2[0], &sum, sizeof(sum));
        printf("Sum : %d\n", sum);

        close(pipe1[1]);
        close(pipe2[0]);
    }
	else 
	{
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], &num1, sizeof(num1));
        read(pipe1[0], &num2, sizeof(num2));

        sum = num1 + num2;

        write(pipe2[1], &sum, sizeof(sum));

        close(pipe1[0]);
        close(pipe2[1]);
        _exit(1);
    }

    return 0;
}
