#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
int main()
{
	int rec, sendFlag;
	socklen_t actualLength;
	char message[50];
	struct sockaddr_in serverAddr, clientAddr;
	int sockFD;
	sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFD == -1)
	{
		printf("\n Socket creating failed. Exiting...");
		exit(0);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(3388);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
	int retVal;
	retVal = bind(sockFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	retVal = listen(sockFD, 1);
	int newSockFD;
	newSockFD = accept(sockFD, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
	rec = recv(newSockFD, message, sizeof(message),0);
	if(rec==-1)
	{
		printf("not recieved");
		close(sockFD);
		close(newSockFD);
	}
	puts(message);
	printf("\n");
	scanf("%s",message);
	sendFlag = send(newSockFD, message, sizeof(message), 0); 
	close(sockFD);
	close(newSockFD);
}