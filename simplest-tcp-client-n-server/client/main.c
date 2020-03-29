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
void sendWelcomeMsg(int);
void recvWelcomeMsg(int);

int main(void)
{
    const int bufSize = 10;
    char buf[bufSize];
	struct sockaddr_in local;
	int csock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
    local.sin_port = htons(60000);
	local.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(!isvalidsocket(csock))
    {
    	printf("Client socket descriptor %d is not valid | code: %d\n", errno, csock);
    	exit(-1);
    }
    funcsResults = connect(csock, (struct sockaddr*)&local, sizeof(local));
    if(funcsResults)
    {
    	printf("Failed to connect | code: %d\n", errno);
    	exit(-1);
    }
    sendWelcomeMsg(csock);
    recvWelcomeMsg(csock);
    close(csock);
}

int isvalidsocket(int s)
{
    return s >= 0;
}

void sendWelcomeMsg(int s)
{
    printf("Sending a welcoming message...\n");
    char buf[4] = "Hi!";
    funcsResults = send(s, buf, sizeof(buf), 0);
    if(funcsResults <= 0)
    {
        printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
        return;
    }
    printf("Sent!\n\n");
}
void recvWelcomeMsg(int s)
{
    printf("Waiting for welcoming message from server side\n");
    const int bufSize = 10;
    char buf[bufSize];
    funcsResults = recv(s, buf, bufSize, 0);
    if(funcsResults <= 0)
    {
        printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
        return;
    }
    printf("%s\n", buf);
    printf("Received!\n\n");
}