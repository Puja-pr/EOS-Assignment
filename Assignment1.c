#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
int ret,cnt,i,j,s;
for(i=1;i<6;i++)
{
	ret = fork();
	if(ret == 0)
	{
	printf("child - %d\n",i);
		for(j=1;j<6;j++)
		{
		cnt++;

		}
		printf("count = %d\n",cnt);
		printf("child pid = %d\n",getpid());
		_exit(0);		
	}

else
{
waitpid(ret,&s,0);

}
}

return 0;
}
