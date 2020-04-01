#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>

struct message
{
    char msg[10];
    int actualrecv;
};

int sendwmsg(int, struct sockaddr_in*);
struct message recvwmsg(int, struct sockaddr_in*);


int main(void)
{
    struct sockaddr_in server;
    struct message wmessage;
    int serverLen = 0;
    int ssock = 0;
    bzero(&server, sizeof(server));
    bzero(&wmessage, sizeof(wmessage));
    server.sin_family = AF_INET;
    server.sin_port = htons(60000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ssock < 0)
    {
        printf("Server socket descriptor %d is not valid | code: %d\n", errno, ssock);
        return -1;
    }
    serverLen = sizeof(server);
    printf("Sending welcoming message to server...\n");
    if(sendwmsg(ssock, &server) <= 0) 
    {
        printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
        return -1;
    }
    printf("Sent!\n\n");
    printf("Waiting for welcoming message from server...\n");
    wmessage = recvwmsg(ssock, &server);
    if(wmessage.actualrecv <= 0)
    {
        printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
        return -1;
    }
    printf("Message from server: %s\n", wmessage.msg);
    printf("Received!\n\n");
    printf("Session close in progress...\n");
    if(close(ssock))
    {
        printf("Unable to close client socket | code: %d\n", errno);
    }
    printf("Session closed.\n\n");
    return 0;
}

int sendwmsg(int s, struct sockaddr_in* server)
{
    int sent = 0;
    sent = sendto(s, "Hi!", 3, 0, (struct sockaddr*)server, sizeof(*server));
    return sent;
}

struct message recvwmsg(int s, struct sockaddr_in* server)
{
    struct message recwm = {"", 0};
    int len = sizeof(*server);
    recwm.actualrecv = recvfrom(s, recwm.msg, sizeof(recwm.msg), 0, (struct sockaddr*)server, &len);
    return recwm;
}