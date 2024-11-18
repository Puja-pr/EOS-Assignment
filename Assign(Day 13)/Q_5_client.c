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
    int ret, cli_fd;
    struct sockaddr_in serv_addr;
    char msg[512];

    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_fd < 0) 
	{
        perror("Socket creation failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);

    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0) 
	{
        perror("Connection failed");
        close(cli_fd);
        return 1;
    }

    do 
	{
        printf("Client: ");
        gets(msg);  
        write(cli_fd, msg, strlen(msg) + 1);

        memset(msg, 0, sizeof(msg)); 
        ret = read(cli_fd, msg, sizeof(msg) - 1);
        if (ret < 0) 
		{
            perror("Read failed");
            break;
        }
        
		printf("Server: %s\n", msg);
    } while (strcmp(msg, "bye") != 0);

    close(cli_fd);
    return 0;
}

