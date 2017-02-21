#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int sockFd, newSockFD, retVal;
	socklen_t actualLen;
	int recedBytes, sentBytes;
	struct sockaddr_in serverAddr, clientAddr;
	char message[50];
	int a = 0;
	sockFd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockFd == 0)
	{
		printf("\n Socket creating failed. Exiting...");
		exit(0);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(3388);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
	retVal = bind(sockFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (retVal == 1)
	{
		printf("\n Binding error! Exiting...");
		close(sockFd);
		exit(0);
	}

	retVal = listen(sockFd, 1);
	if(retVal==-1)
	{
		printf("Retval returned -1. Exiting...\n");
		close(sockFd);
		exit(0);
	}

	actualLen = sizeof(clientAddr);	
	newSockFD = accept(sockFd, (struct sockaddr*)&clientAddr, &actualLen);

	if(newSockFD = -1)
	{
		printf("New sockFD creation problem. Exiting...\n");
	}

	recedBytes = recv(newSockFD, message, sizeof(message), 0);

	if(recedBytes = -1)
	{
		close(sockFd);
		close(newSockFD);
	}
	puts(message);
	printf("\n");
	scanf("%s",message);
	sentBytes = send(newSockFD,message, sizeof(message),0);
	close(sockFd);
	close(newSockFD);

}