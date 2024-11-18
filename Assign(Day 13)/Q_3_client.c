#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
    int ret, cli_fd;
    struct sockaddr_un serv_addr;
    int num1, num2, sum;
    const char *socket_path = "/tmp/mysock";  

    cli_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cli_fd == -1) 
	{
        perror("socket");
        return 1;
    }

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, socket_path);
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == -1) 
	{
        perror("connect");
        return 1;
    }

    printf("Connected to server.\n");

    while (1) 
	{
        printf("Enter first number: ");
        scanf("%d", &num1);
        printf("Enter second number: ");
        scanf("%d", &num2);

        if (write(cli_fd, &num1, sizeof(num1)) <= 0) 
		{
            perror("write num1");
            break;
        }
        if (write(cli_fd, &num2, sizeof(num2)) <= 0) 
		{
            perror("write num2");
            break;
        }

        if (read(cli_fd, &sum, sizeof(sum)) <= 0) 
		{
            perror("read sum");
            break;
        }

        printf("Server: The sum is %d\n", sum);

        if (num1 == 0 && num2 == 0) 
		{
            break;
        }
    }

    close(cli_fd);

    return 0;
}

