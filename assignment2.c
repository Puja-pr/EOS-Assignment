#include<stdio.h>
#include<unistd.h>
 #include <sys/wait.h>


//parent->child1->child2->child->3

int main()
{
	int pid1,pid2,pid3,i,s1,s2,s3;
	pid1 = fork();
	if (pid1 == 0)//child 1
	{
		
		pid2 = fork();
		if(pid2 == 0)//child2
			{
			pid3 = fork();
				if(pid3 == 0) //child3
				{
					for(i=1;i<=5;i++)
					{
						printf("child D - %d \n",i);
						sleep(1);
					}
					
				_exit(0);

				}
			
		else{		
		for(i=1;i<=5;i++)
			{
				printf("child C - %d \n",i);
				sleep(1);
			}
			waitpid(pid3,&s2,0);
			_exit(0);

			}
			}
	else{		
		for(i=1;i<=5;i++)
		{
		printf("child B - %d\n",i);
		sleep(1);
		}
		waitpid(pid2,&s1,0);
		_exit(0);

		}
	}	
	else
	{
	for(i=1;i<=5;i++)
		{
			printf("parent A - %d\n",i);
			sleep(1);
		}
		waitpid(pid1,&s1,0);
	}
return 0;
}
