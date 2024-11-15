//From one parent create 5 child processes. Each child should run for 5 seconds and print count along with its pid. Parent should wait for all child processes to complete and clean all of them. Hint: use loop to fork() multiple child processes
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void run_process(const char* name); 

int main() {
    int i, pid1, pid2, pid3, pid4, pid5, s1, s2, s3, s4 , s5, s;

    pid1 = fork();
    if(pid1 == 0) {
        run_process("Child 1");
        _exit(3);
    }

    pid2 = fork();
    if(pid2 == 0) {
        run_process("Child 2");
        _exit(7);
    }

    pid3 = fork();
    if(pid3 == 0) {
        run_process("Child 3");
        _exit(9);
    }

    pid4 = fork();
    if(pid4 == 0) {
        run_process("Child 4");
        _exit(17);
    }
    
    pid5 = fork();
    if(pid5 == 0) {
        run_process("Child 5");
        _exit(22);
    }
    
    for(i=1; i<=3; i++) {
        printf("parent: %d\n", i);
        sleep(1);
    }

    while(waitpid(-1, &s, 0) > 0)
        printf("child exit status: %d\n", WEXITSTATUS(s));
    return 0;
}

void run_process(const char* name) {
    for (int i = 1; i <= 5; i++) {
        printf("%s: %d\n", name, i);
        sleep(1);
    }
}

