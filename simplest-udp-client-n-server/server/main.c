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
	struct sockaddr_in local;
    struct sockaddr_in client;
    struct message wmessage;
    int clientLen = 0;
    int ssock = 0;
    bzero(&local, sizeof(local));
    bzero(&client, sizeof(client));
    bzero(&wmessage, sizeof(wmessage));
	local.sin_family = AF_INET;
    local.sin_port = htons(60000);
	local.sin_addr.s_addr = htons(INADDR_ANY);
	ssock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ssock < 0)
    {
    	printf("Server socket descriptor %d is not valid | code: %d\n", errno, ssock);
    	return -1;
    }
    if(bind(ssock, (struct sockaddr*)&local, sizeof(local)))
    {
    	printf("Failed to bind socket | code: %d\n", errno);
    	return -1;
    }
    while(1)
    {
        clientLen = sizeof(client);
        printf("Waiting for welcoming message...\n");
        wmessage = recvwmsg(ssock, &client);
        if(wmessage.actualrecv <= 0)
        {
            printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
            continue;
        }
        printf("Message from client: %s\n", wmessage.msg);
        printf("Received\n\n");
        printf("Sending welcoming message...\n");
        if (sendwmsg(ssock, &client) <= 0) 
        {
            printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
            continue;
        }
        printf("Sent!\n\n");
    }
    printf("Server closing in progress...\n");
	if(close(ssock))
	{
		printf("Unable to close server socket | code: %d\n", errno);
	}
    printf("Server closed.\n\n");
    return 0;
}

int sendwmsg(int s, struct sockaddr_in* server)
{
    int sent = 0;
    sent = sendto(s, "Hello!", 6, 0, (struct sockaddr*)server, sizeof(*server));
    return sent;
}

struct message recvwmsg(int s, struct sockaddr_in* server)
{
    struct message recwm = {"", 0};
    int len = sizeof(*server);
    recwm.actualrecv = recvfrom(s, recwm.msg, sizeof(recwm.msg), 0, (struct sockaddr*)server, &len);
    return recwm;
}