#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

int main()
{
	int sockFD;
	sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFD == -1)
	{
		printf("Socket creation error\n");
	}

	struct sockaddr_in serverAddress, clientAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(1232);
	serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

	int bindSocket;
	bindSocket = bind(sockFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if(bindSocket == -1)
	{
		printf("Binding error\n");
		close(sockFD);
	}

	int listenValue = 0;
	listenValue = listen(sockFD, 0);
	if(listenValue == -1)
	{
		printf("Listen error\n");
		close(sockFD);
	}

	socklen_t clientAddressLength;
	int newSockFD;
	newSockFD = accept(sockFD, (struct sockaddr*)&clientAddress, &clientAddressLength);

	if(newSockFD == -1)
	{
		printf("Accept error\n");
		close(newSockFD);
		close(sockFD);
	}

	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		char message[50];
		int recievedKiValue = recv(newSockFD, message, sizeof(message),0);
		if(recievedKiValue == -1)
		{
			printf("Recieving error\n");
			close(newSockFD);
			close(sockFD);
		}
		else
		{
			printf("%s\n", message);
		}

	}

	else
	{
		char message[50];
		scanf("%s",message);
		int sendKiValue;
		sendKiValue = send(newSockFD, message, sizeof(message),0);
	}

	close(sockFD);
	close(newSockFD);



}