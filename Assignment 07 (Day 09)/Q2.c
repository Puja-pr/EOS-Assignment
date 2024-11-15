//From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these processes should run concurrently for 5 seconds and cleaned up properly upon termination

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void run_process(const char* name);

int main() {

int pid1, pid2, pid3, s1, s2, s3;

pid1 = fork();
if(pid1 == 0) 
{
	pid2 = fork();
	if(pid2 == 0)
	{
		pid3 = fork();
		if(pid3 == 0)
		{
			run_process("Child D");
		_exit(3);
		}
		else 
		{
			run_process("Child C");
			wait(&s3);
			printf("Exit Status : %d\n",WEXITSTATUS(s3));
		} 
	_exit(2);
	}
	else 
	{
		run_process("Child B");
		wait(&s2);
		printf("Exit Status : %d\n",WEXITSTATUS(s2));
	}		
_exit(1);
}
else 
{
	run_process("Parent[A]");
	wait(&s1);
	printf("Exit Status : %d\n",WEXITSTATUS(s1));
}

return 0;
}

void run_process(const char* name) {
    for (int i = 1; i <= 5; i++) {
        printf("%s: %d\n", name, i);
        sleep(1);
    }
}
