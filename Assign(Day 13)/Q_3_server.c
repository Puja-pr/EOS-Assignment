#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
    int ret, serv_fd, cli_fd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    int num1, num2, sum;
    const char *socket_path = "/tmp/mysock";  

    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    
	if (serv_fd == -1) 
	{
        perror("socket");
        return 1;
    }

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, socket_path);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
	if (ret == -1) 
	{
        perror("bind");
        return 1;
    }

    ret = listen(serv_fd, 5);
    
	if (ret == -1) 
	{
        perror("listen");
        return 1;
    }

    printf("Waiting..........\n");

    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    
	if (cli_fd == -1) 
	{
        perror("accept");
        return 1;
    }

    printf("Client connected.\n");

    while (1) 
	{
        if (read(cli_fd, &num1, sizeof(num1)) <= 0) 
		{
            perror("read num1");
            break;
        }
        
		if (read(cli_fd, &num2, sizeof(num2)) <= 0) 
		{
            perror("read num2");
            break;
        }

        printf("Numbers Got: %d and %d\n", num1, num2);

        sum = num1 + num2;
        printf("Sending sum: %d\n", sum);

        if (write(cli_fd, &sum, sizeof(sum)) <= 0) 
		{
            perror("write sum");
            break;
        }

        if (num1 == 0 && num2 == 0) 
		{
            break;
        }
    }

    close(cli_fd);

    shutdown(serv_fd, SHUT_RDWR);

    unlink(socket_path);

    return 0;
}

