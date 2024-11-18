#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    int fd_write, fd_read, ret;
    char buf[32];
    int num1, num2;

    fd_write = open("/tmp/myfifo", O_WRONLY);
    if(fd_write < 0) 
	{
        perror("open() failed");
        _exit(1);
    }

    fd_read = open("/tmp/myfifo_result", O_RDONLY);
    if(fd_read < 0) 
	{
        perror("open() failed");
        _exit(1);
    }

    printf("Client: enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    sprintf(buf, "%d %d", num1, num2);
    ret = write(fd_write, buf, strlen(buf) + 1);

    ret = read(fd_read, buf, sizeof(buf));
    printf("Client: result received: %s\n", buf);

    close(fd_write);
    close(fd_read);

    return 0;
}
