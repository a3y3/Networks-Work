#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
	int sockFD, newSockFD, sendCheck, recieveCheck;
	socklen_t clientLength;
	struct sockaddr_in serverAddr, clientAddr;
	sockFD = socket(AF_INET, SOCK_STREAM, 0);	
	if(sockFD == -1)
	{
		printf("Error initating socket. Please try again\n");
	}
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(3333);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
	int bindCheck;
	bindCheck = bind(sockFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(bindCheck == -1)
	{
		printf("Error binding server to server address\n");
		close(sockFD);
	}
	char message[50];
	
		
	int listenCheck;
	listenCheck = listen(sockFD, 1);
	if(listenCheck == -1)
	{
		printf("Somehow, just somehow, listen could not initialize\n");
		close(sockFD);
	}

	clientLength = sizeof(clientAddr);
	newSockFD = accept(sockFD, (struct sockaddr*)&clientAddr, &clientLength);
	if(newSockFD == -1)
	{
		printf("A new sockFD could not be initialized\n");
		close(sockFD);
	}
	
	do
	{
		recieveCheck == recv(newSockFD, message, sizeof(message),0);
		if(recieveCheck == -1)
		{
			printf("We're having problems recieving the message you just sent. Why not try again?\n");
			close(newSockFD);
			close(sockFD);
		}
		if(strcmp(message,"stop")==0)
		{
			printf("stop recieved. Exiting...");
			close(sockFD);
			close(newSockFD);
			exit(1);
		}
	

		printf("Trying to open %s\n",message);
		FILE *file;
		file = fopen(message,"r+");
		char s[1000];
		int i = 0;
		char randomchar;
		if(file!=NULL)
		{
			char ch;
			ch = fgetc(file);
			while(ch != EOF)
			{
				s[i++] = ch;
				ch = fgetc(file);
			}
		}
		else
			printf("\nFile doesn't exist\n");
			
		sendCheck = send(newSockFD, s, sizeof(s), 0);
		if(sendCheck == -1)
		{
			printf("Trouble sending message back to you\n");
	
		}
		
	}while(strcmp(message,"stop")!=0);
	printf("reached here");
	close(sockFD);
	close(newSockFD);
}	
