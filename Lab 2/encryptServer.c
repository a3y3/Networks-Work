#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

int main()
{
	int sockfd, newsockfd, retval;
	socklen_t actuallen;
	int recedbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr;

	char buff[MAXSIZE];
	int a = 0;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1)
	{
		printf("\nSocket creation error");
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(3388);
	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
	retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == 1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval = listen(sockfd, 1);
	if (retval == -1)
	{
		close(sockfd);
	}

	actuallen = sizeof(clientaddr);
	newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);


	if (newsockfd == -1)
	{
		close(sockfd);
	}
	recedbytes = recv(newsockfd, buff, sizeof(buff), 0);

	if (recedbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}


	char newBuff[50];
	int l = strlen(buff);
	int i = 0;
	for(i = 0;i<l;i++)
	{
		if(i>=65&&i<=92)
		{
			newBuff[i]=buff[i]-15;
		}
		else
		{
			newBuff[i]=buff[i]-48;
		}
	}

	printf("\n");
	sentbytes = send(newsockfd, newBuff, sizeof(buff), 0);

	if (sentbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}

	close(sockfd);
	close(newsockfd);
}
