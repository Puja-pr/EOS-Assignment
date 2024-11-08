#include<stdio.h>
   #include <sys/types.h>
       #include <signal.h>

int main()
{
int s,pid,ret;
	printf("signal no :");
	scanf("%d",&s);
	printf("process id : ");
	scanf("%d",&pid);
ret = kill(pid,s);
	if(ret == 0)
	{
	printf("kill suceessful\n");
	}
else
	perror("kill() failed");




return 0;
}
