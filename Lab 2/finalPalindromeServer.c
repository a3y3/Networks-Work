#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>


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
	int flag = 0, i = 0;
	for (i = 0; i < strlen(buff); i++)
	{
		if (buff[i] != buff[strlen(buff) - 1 - i])
		{
			flag = 1;
		}
		else
			continue;
	}
	if (flag == 0)
	{
		strcpy(newBuff,"Palindrome");
	}
	else
		strcpy(newBuff,"Not palindrome");

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

