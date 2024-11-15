// Implement asynchronous execution in your shell i.e. if command suffixed with &, then shell should not wait for the child process. Ensure that process isn't left zombie.
//	Eg. ---> //	firefox &

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void sig_handler(int sig) {
    printf("SIGINT caught: %d\n", sig);
} 	

int main() {
    char cmd[512], *ptr, *args[32];
    int shell, i = 0, s, err, ret;
    struct sigaction sa;
    
    //struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = sig_handler;
    sigaction(SIGCHLD, &sa, NULL);
    
    while(1) {
        
        printf("cmd> ");
	gets(cmd);
	
	if (strlen(cmd) == 0) {
            continue; 
        }
	
	i = 0;
        ptr = strtok(cmd, " ");
        while (ptr != NULL) {
            args[i] = ptr;
            i++;
            ptr = strtok(NULL, " ");
        }
        args[i] = NULL;
        
        if(strcmp(args[0], "exit") == 0)
            _exit(0);
        else if(strcmp(args[0], "cd") == 0)
            chdir(args[1]);
            
	else  {
		int shell = fork();

		if (shell < 0) 
    			perror("Fork failed");
		else if (shell == 0) {
    			if (execvp(args[0], args) < 0) {
        			perror("Exec() Failed");
        			_exit(1);
    			}
		} else {
                	if (args[i-1] && strcmp(args[i-1], "&") == 0) {
                    		args[i-1] = NULL;
                	} else {
                    		waitpid(shell, NULL, 0); 
                    	}
            	}
        }
    }
    return 0;
}
