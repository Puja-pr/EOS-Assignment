// The child process send two numbers to the parent process via message queue. The parent process calculate the sum and return via same message queue. The child process print the result and exit. The parent process wait for completion of the child and then exit

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY	0x1234

typedef struct msg {
	long id;
	int num1;
	int num2;
	int result;
}msg_t;

int main() {
	int mqid, pid, s, ret;
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid <0){
	perror("msgget() failed\n");
	_exit(1);
	}
	
	pid = fork();
	if(pid == 0){
		msg_t M1;
		M1.id = 100;
		
		printf("Enter Num1 : ");
		scanf("%d",&M1.num1);
		printf("Enter Num2 : ");
		scanf("%d",&M1.num2);
		ret = msgsnd(mqid, &M1, sizeof(msg_t)-sizeof(long), 0);
		
		if(ret < 0){
			perror("msgsnd failed\n");
			} else {
			printf("Nums Sent : %d & %d.\n", M1.num1, M1.num2);
		}
		
		ret = msgrcv(mqid, &M1, sizeof(msg_t) - sizeof(long), 200, 0);
        	if (ret < 0) {
            		perror("msgrcv() failed\n");
        		} else {
            			printf("Sender received [RESULT]: %d\n", M1.result);
        	}
			
	} else {
		msg_t M2;
		printf("Receiver Waiting For Response\n");
        	ret = msgrcv(mqid, &M2, sizeof(msg_t)-sizeof(long), 100, 0);
        	
        	
        	
        	if(ret < 0)
            		perror("msgrcv() failed");
        	else
            		printf("Receiver Got : %d & %d\n", M2.num1, M2.num2);
            	
            	M2.result = M2.num1 + M2.num2;
        	M2.id = 200;
        	ret = ret = msgsnd(mqid, &M2, sizeof(msg_t)-sizeof(long), 0);	
            	if (ret < 0) {
               		perror("msgsnd() failed");
            		} else {
            			printf("Sender Received Sum\n");
            	}
            		
        waitpid(pid, &s, 0);
        msgctl(mqid, IPC_RMID, NULL);
	}

return 0;
}
