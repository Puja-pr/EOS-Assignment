#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_ADDR   "127.0.0.1"
#define SERV_PORT   2809

int main() 
{
    int ret, serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    char msg[512];

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    
	if (serv_fd < 0) 
	{
        perror("Socket creation failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);

    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
	if (ret < 0) 
	{
        perror("Bind failed");
        close(serv_fd);
        return 1;
    }

    ret = listen(serv_fd, 5);
    
	if (ret < 0) 
	{
        perror("Listen failed");
        close(serv_fd);
        return 1;
    }

    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    
	if (cli_fd < 0) 
	{
        perror("Accept failed");
        close(serv_fd);
        return 1;
    }

    do 
	{
        memset(msg, 0, sizeof(msg)); // Clear buffer
        ret = read(cli_fd, msg, sizeof(msg) - 1);
        
		if (ret < 0) 
		{
            perror("Read failed");
            break;
        }
        printf("Client: %s\n", msg);

        printf("Server: ");
        gets(msg);  
        write(cli_fd, msg, strlen(msg) + 1);
    } while (strcmp(msg, "bye") != 0);

    close(cli_fd);
    
	close(serv_fd);
    
	return 0;
}

