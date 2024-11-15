#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid[7];
    int s, err;

    pid[1] = fork();
    if (pid[1] == 0) { 
        char *args[] = {"gcc", "-c", "circle.c", NULL};
        err = execv("/usr/bin/gcc", args);
        perror("exec() failed");
        _exit(1);
    }

    pid[2] = fork();
    if (pid[2] == 0) { 
        char *args[] = {"gcc", "-c", "square.c", NULL};
        err = execv("/usr/bin/gcc", args);
        perror("exec() failed");
        _exit(1);
    }

    pid[3] = fork();
    if (pid[3] == 0) { 
        char *args[] = {"gcc", "-c", "rectangle.c", NULL};
        err = execv("/usr/bin/gcc", args);
        perror("exec() failed");
        _exit(1);
    }

    pid[4] = fork();
    if (pid[4] == 0) { 
        char *args[] = {"gcc", "-c", "main.c", NULL};
        err = execv("/usr/bin/gcc", args);
        perror("exec() failed");
        _exit(1);
    }

    int success = 1;
    for (int j = 1; j <= 4; j++) {
        waitpid(pid[j], &s, 0);
        printf("Child %d exit status: %d\n", j, WEXITSTATUS(s));
        if (WEXITSTATUS(s) != 0) {
            success = 0;
        }
    }

    if (success) {
        pid[5] = fork();
        if (pid[5] == 0) {
            char *linkargs[] = {"gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL};
            err = execv("/usr/bin/gcc", linkargs);
            perror("Linking failed");
            _exit(1);
        }

        waitpid(pid[5], &s, 0);
        printf("Linking exit status: %d\n", WEXITSTATUS(s));

        if (WEXITSTATUS(s) == 0) {
            pid[6] = fork();
            if (pid[6] == 0) {
                char *args[] = {"./program.out", NULL};
                err = execvp("./program.out", args);
                perror("Execution failed");
                _exit(1);
            }

            waitpid(pid[6], &s, 0);
            printf("Execution exit status: %d\n", WEXITSTATUS(s));
        }
    }

    return 0;
}
