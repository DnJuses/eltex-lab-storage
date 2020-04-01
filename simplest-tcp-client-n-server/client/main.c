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

int sendwmsg(int);
struct message recvwmsg(int);

int main(void)
{
	struct sockaddr_in local;
    struct message wmessage;
	int csock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&wmessage, sizeof(wmessage));
    bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
    local.sin_port = htons(60000);
	local.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(csock < 0)
    {
    	printf("Client socket descriptor %d is not valid | code: %d\n", errno, csock);
    	return -1;
    }
    printf("Connecting to %s:%d...\n", inet_ntoa(local.sin_addr), ntohs(local.sin_port));
    if(connect(csock, (struct sockaddr*)&local, sizeof(local)))
    {
    	printf("Failed to connect | code: %d\n", errno);
    	return -1;
    }
    printf("Connected!\n\n");
    printf("Sending a welcoming message...\n");
    if(sendwmsg(csock) < 0)
    {
        printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
        return -1;
    }
    printf("Sent!\n\n");
    printf("Waiting for welcoming message from server side\n");
    wmessage = recvwmsg(csock);
    if(wmessage.actualrecv <= 0)
    {
        printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
        return -1;
    }
    printf("Message from server: %s\n", wmessage.msg);
    printf("Received!\n\n");
    printf("Closing client's session...\n");
    if(close(csock))
    {
        printf("Failed to close client socket\n");
    }
    printf("Session successfully closed.\n");
    return 0;
}

int sendwmsg(int s)
{
    char buf[3] = "Hi!";
    int sent = send(s, buf, sizeof(buf), 0);
    return sent;
}
struct message recvwmsg(int s)
{
    struct message recvm = {"", 0};
    recvm.actualrecv = recv(s, recvm.msg, sizeof(recvm.msg), 0);
    return recvm;
}