#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>

static int funcsResults = 0;

int isvalidsocket(int);
void startServer(int);

int main(void)
{
	struct sockaddr_in local;
    int ssock = 0;
    bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
    local.sin_port = htons(60000);
	local.sin_addr.s_addr = htons(INADDR_ANY);
	ssock = socket(AF_INET, SOCK_DGRAM, 0);
    if(!isvalidsocket(ssock))
    {
    	printf("Server socket descriptor %d is not valid | code: %d\n", errno, ssock);
    	exit(-1);
    }
    funcsResults = bind(ssock, (struct sockaddr*)&local, sizeof(local));
    if(funcsResults < 0)
    {
    	printf("Failed to bind socket | code: %d\n", errno);
    	exit(-1);
    }
    startServer(ssock);
    printf("Server closing in progress...\n");
    funcsResults = close(ssock);
	if(funcsResults)
	{
		printf("Unable to close server socket | code: %d\n", errno);
	}
    printf("Server closed.\n");
    exit(0);
}

int isvalidsocket(int s)
{
	return s >= 0;
}

void startServer(int s)
{
    struct sockaddr_in client;
    int clientLen = 0;
    char buf[3] = "";
    do
    {
        clientLen = sizeof(client);
        funcsResults = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&client, &clientLen);
        if(funcsResults >= 0)
        {
            printf("Client connected\n");
            printf("Sending pong to client...\n");
            funcsResults = sendto(s, "", 1, 0, (struct sockaddr*)&client, clientLen);
            if (funcsResults < 0) 
            {
                printf("Error accured during pong sending | code: %d\n", errno);
                return;
            }
            printf("Waiting for welcoming message...\n");
            funcsResults = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&client, &clientLen);
            if (funcsResults < 0) 
            {
                printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
                return;
            }
            printf("Message: %s\n", buf);
            printf("Sending welcoming message...\n");
            funcsResults = sendto(s, "Hello!", 6, 0, (struct sockaddr*)&client, clientLen);
            if (funcsResults < 0) 
            {
                printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
                return;
            }
            printf("Sent!\n");
        }
    } while(0);
}