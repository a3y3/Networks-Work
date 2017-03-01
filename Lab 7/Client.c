#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>

int main()
{
	int sockfd, retval; int sig;
	int sentbytes, rcvbytes;
	struct sockaddr_in serveraddr;
	char buffer[100];
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		printf("\nSocket nahi bana.");
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3333);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	socklen_t len;
	len = sizeof(serveraddr);
	int pid;
	scanf("%s",buffer);
	sentbytes = sendto(sockfd, buffer, sizeof(buffer),0,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
	pid = fork();
	while(1)
	{
		
		if(pid > 0)
		{
			rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, &len);
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
				sentbytes = sendto(sockfd, "bye", sizeof("bye"),0,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
				if(sentbytes == -1)
				{
					close(sockfd);
				}
				kill(getpid(),sig);
				close(sockfd);
				exit(0);
			}
			sentbytes = sendto(sockfd, buffer, sizeof(buffer),0,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
			if(sentbytes == -1)
			{
				close(sockfd);
			}
			
		}

	}
	close(sockfd);
}
