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

struct message recvwmsg(int); // Receive welcoming message from client
int sendwmsg(int); // Send welcoming message to client
void closeconnect(int); // Close connection on socket

int main(void)
{
	struct sockaddr_in local;
	struct sockaddr_in client;
	int clientLen = 0;
	int csock = 0;
    int ssock = 0;
    bzero(&local, sizeof(local));
    bzero(&client, sizeof(client));
	local.sin_family = AF_INET;
    local.sin_port = htons(60000);
	local.sin_addr.s_addr = htons(INADDR_ANY);
	ssock = socket(AF_INET, SOCK_STREAM, 0);
    if(ssock < 0)
    {
    	printf("Server socket descriptor %d is not valid | code: %d\n", errno, ssock);
    	return -1;
    }
    if(bind(ssock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
    	printf("Failed to bind socket | code: %d\n", errno);
    	return -1;
    }
    if(listen(ssock, 5) < 0)
    {
    	printf("Failed to set socket to listen | code: %d\n", errno);
    	return -1;
    }
    printf("Listening on port 60000....\n\n");
    while(1)
    {
    	clientLen = sizeof(client);
        csock = -2;
    	csock = accept(ssock, (struct sockaddr*)&client, &clientLen);
    	if(csock < 0)
    	{
    		printf("Client socket descriptor %d is not valid | code: %d\n", errno, csock);
    		continue;
    	}
        printf("Incoming connection...\nSocket Descriptor: %d\nAddress: %s\n\n", csock, inet_ntoa(client.sin_addr));
        printf("Waiting for welcoming message from client side\n");
        struct message wmessage = recvwmsg(csock);
    	if(wmessage.actualrecv <= 0)
        {
            printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
            closeconnect(csock);
            continue;
        }
        printf("Message from client: %s\n", wmessage.msg);
        printf("Received!\n\n");
        printf("Sending a welcoming message...\n");
    	if(sendwmsg(csock) <= 0)
        {
            printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
            closeconnect(csock);
            continue;
        }
        printf("Sent!\n\n");
    	printf("Closing connection with address %s\n", inet_ntoa(client.sin_addr));
        closeconnect(csock);
        printf("Closed!\n\n");
    }
    closeconnect(ssock);
    return 0;
}

struct message recvwmsg(int s)
{
    struct message recvm = {"", 0};
    recvm.actualrecv = recv(s, recvm.msg, sizeof(recvm.msg), 0);
    return recvm;
}


int sendwmsg(int s)
{
	char buf[6] = "Hello!";
	int sent = send(s, buf, sizeof(buf), 0);
    return sent;
}

void closeconnect(int s)
{
    if(close(s))
    {
        printf("Unable to close socket %d | code: %d\n", s, errno);
    }
}