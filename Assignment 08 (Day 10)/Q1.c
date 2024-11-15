//Input signal number and a process id from user. Send given signal to the given process using kill() syscall.

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    int sig_no = atoi(argv[1]);
    pid_t PID = (pid_t)atoi(argv[2]);

    printf("Signal number: %d \n", sig_no);
    printf("Process ID: %d \n", PID);

    int ret = kill(PID, sig_no);
    if (ret == -1) {
        perror("kill");
        exit(1);
    }

    printf("Signal sent successfully!\n");
    return EXIT_SUCCESS;
}
