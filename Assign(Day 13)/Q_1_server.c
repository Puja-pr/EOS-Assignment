#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    int fd_read, fd_write, ret;
    char buf[32];
    int num1, num2, sum;

    mkfifo("/tmp/myfifo", 0666);
    mkfifo("/tmp/myfifo_result", 0666);

    fd_read = open("/tmp/myfifo", O_RDONLY);
    
	if(fd_read < 0) 
	{
        perror("open() failed");
        _exit(1);
    }

    fd_write = open("/tmp/myfifo_result", O_WRONLY);
    
	if(fd_write < 0) 
	{
        perror("open() failed");
        _exit(1);
    }

    printf("Server: waiting for message...\n");
    ret = read(fd_read, buf, sizeof(buf));
    sscanf(buf, "%d %d", &num1, &num2);
    printf("Server: received numbers: %d, %d\n", num1, num2);

    sum = num1 + num2;

    sprintf(buf, "%d", sum);
    ret = write(fd_write, buf, strlen(buf) + 1);
    printf("Server: result sent: %s\n", buf);

    close(fd_read);
    close(fd_write);

    return 0;
}
