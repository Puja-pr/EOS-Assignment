//Improve your shell program so that it should not be terminated due to SIGINT (ctrl+C).

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void sigint_handler(int sig) {
    printf("SIGINT caught: %d\n", sig);
} 	

int main() {
	
char cmd[512], *ptr, *args[32];
int shell, i=0, s, err;

signal(SIGINT, sigint_handler);
	
while(1){
		
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
        else if(strcmp(args[0], "history") == 0)
            chdir(args[1]);
	else {
		shell = fork();
		if(shell == 0){
			err = execvp(args[0], args);
			if(err < 0){
				perror("Exec() Failed");
				_exit(0);
			}
		} else 
			waitpid(-1, &s, 0);
        }
        
}

return 0;
}
