//Write a program that will launch two programs (e.g. who and wc). The output of first program (e.g. who) should be given as input to second program (e.g.wc)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    int pid1, pid2, s;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        _exit(1);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        _exit(1);
    }

    if (pid1 == 0) { 
        close(pipefd[0]); 
        dup2(pipefd[1], 1); 
        close(pipefd[1]);
        execlp("who", "who", NULL);
        perror("execlp who");
        _exit(1);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        _exit(1);
    }

    if (pid2 == 0) {
        close(pipefd[1]); 
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        _exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, &s, 0);
    waitpid(pid2, &s, 0);

    return 0;
}
