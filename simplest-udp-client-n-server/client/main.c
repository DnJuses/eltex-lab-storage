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
void startClient(int, struct sockaddr_in*);

int main(void)
{
    struct sockaddr_in server;
    int csock = 0;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(60000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    csock = socket(AF_INET, SOCK_DGRAM, 0);
    if(!isvalidsocket(csock))
    {
        printf("Server socket descriptor %d is not valid | code: %d\n", errno, csock);
        exit(-1);
    }
    startClient(csock, &server);
    printf("Session closing in progress...\n");
    funcsResults = close(csock);
    if(funcsResults)
    {
        printf("Unable to close client socket | code: %d\n", errno);
    }
    printf("Session closed.\n");
    exit(0);
}

int isvalidsocket(int s)
{
    return s >= 0;
}

void startClient(int s, struct sockaddr_in *server)
{
    int serverLen = 0;
    char buf[6] = "";
    serverLen = sizeof(*server);
    printf("Sending ping to server...\n");
    funcsResults = sendto(s, "", 1, 0, (struct sockaddr*)server, serverLen);
    if (funcsResults < 0)
    {
        printf("Error accured during connection attempt | code: %d\n", errno);
        return;
    }
    printf("Waiting pong from server...\n");
    funcsResults = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)server, &serverLen);
    if (funcsResults < 0)
    {
        printf("Error accured during connection verification from server | code: %d\n", errno);
        return;
    }
    printf("Connection established successfully\n");
    printf("Sending welcoming message to server...\n");
    funcsResults = sendto(s, "Hi!", 3, 0, (struct sockaddr*)server, serverLen);
    if (funcsResults < 0) 
    {
        printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
        return;
    }
    printf("Sent!\n");
    printf("Waiting for welcoming message from server...\n");
    funcsResults = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)server, &serverLen);
    if (funcsResults < 0) 
    {
        printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
        return;
    }
    printf("Message: %s\n", buf);
}