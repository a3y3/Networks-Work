#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>

int main()
{
	int sockfd, newsockfd, retval; int sig;
	socklen_t actlen;
	int rcvbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr;
	char buffer[100]; 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
		printf("\nSocket nahi bana.");
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3333);
	serveraddr.sin_addr.s_addr=inet_addr("172.16.53.78");
	retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(retval == -1)
	{
		printf("\nBind nahi hua.");
		close(sockfd);
	}
	
	actlen = sizeof(clientaddr);
	
	int pid;
	rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &actlen);
	pid = fork();
	while(1)
	{
		
		if(pid == 0)
		{
			rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &actlen);
			if(rcvbytes == -1)
			{
				close(sockfd);
			}
			puts(buffer);
			printf("\n");
			if(strcmp(buffer, "bye")==0)
			{
				kill(getpid(),sig);
				close(sockfd);
				exit(0);
			}
			
		}
		else
		{
			gets(buffer);
			if(strcmp(buffer, "bye")==0)
			{
				sentbytes = sendto(sockfd, "bye", sizeof("bye"),0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
				if(sentbytes == -1)
				{
					close(sockfd);
				}
				kill(getpid(),sig);
				close(sockfd);
				exit(0);
			}
			sentbytes = sendto(sockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
			if(sentbytes == -1)
			{
				close(sockfd);
			}
			
		}

	}
	close(sockfd);
}
