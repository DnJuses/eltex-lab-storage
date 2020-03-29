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
int verifyConnection(int);
void sendWelcomeMsg(int);
void recvWelcomeMsg(int);

int main(void)
{
	struct sockaddr_in local;
	struct sockaddr_in client;
	const int on = 1;
	int clientLen = 0;
	int csock = 0;
    int ssock = 0;
    bzero(&local, sizeof(local));
    bzero(&client, sizeof(client));
	local.sin_family = AF_INET;
    local.sin_port = htons(60000);
	local.sin_addr.s_addr = htons(INADDR_ANY);
	ssock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
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
    funcsResults = listen(ssock, 5);
    if(funcsResults < 0)
    {
    	printf("Failed to set socket to listen | code: %d\n", errno);
    	exit(-1);
    }
    printf("Listening on port 60000....\n\n");
    do 
    {
    	clientLen = sizeof(client);
    	csock = accept(ssock, (struct sockaddr*)&client, &clientLen);
    	printf("Incoming connection...\nSocket Descriptor: %d\nAddress: %s\n\n", csock, inet_ntoa(client.sin_addr));
    	if(!isvalidsocket(csock))
    	{
    		printf("Client socket descriptor %d is not valid | code: %d\n", errno, csock);
    		exit(-1);
    	}
    	recvWelcomeMsg(csock);
    	sendWelcomeMsg(csock);
    	printf("Closing connection with address %s\n", inet_ntoa(client.sin_addr));
    	funcsResults = close(csock);
    	if(funcsResults)
    	{
    		printf("Unable to close connection with socket | code: %d\n", errno);
    	}
    } while(0); // For now we only looking for 1 connection
    			// If more is needed, just change cycle pred from 0 to 1
    funcsResults = close(ssock);
	if(funcsResults)
	{
		printf("Unable to close server socket | code: %d\n", errno);
	}
    exit(0);
}

int isvalidsocket(int s)
{
	return s >= 0;
}

void sendWelcomeMsg(int s)
{
	printf("Sending a welcoming message...\n");

	char buf[7] = "Hello!";
	funcsResults = send(s, buf, sizeof(buf), 0);
	if(funcsResults <= 0)
	{
		printf("Error accured during welcome message transmission from server to client | code: %d\n", errno);
		return;
	}
	printf("Sent!\n\n");
}

void recvWelcomeMsg(int s)
{
	printf("Waiting for welcoming message from client side\n");
	const int bufSize = 10;
	char buf[bufSize];
	funcsResults = recv(s, buf, bufSize, 0);
	if(funcsResults <= 0)
	{
		printf("Error accured during welcome message transmission from client to server | code: %d\n", errno);
		return;
	}
	printf("%s\n", buf);
	printf("Received!\n\n");
}
