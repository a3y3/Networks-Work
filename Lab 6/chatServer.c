#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

main()
{
	int sockfd,retval;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;

	char buff[MAXSIZE];
	int a=0;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	if(sockfd==-1)
	{
		printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
	{
		printf("Binding error");
		close(sockfd);
	}

	pid_t pid;
	pid = fork();
	while(1)
	{
		if(pid == 0)
		{
			printf("in server child");
			actuallen=sizeof(clientaddr);
			recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,&(actuallen));
			if(recedbytes==-1)
			{
				close(sockfd);
			}

			printf("The string is%s",buff);
			if(strcmp(buff,"exit")==0)
			{
				close(sockfd);
				break;
			}
		}
		else
		{
			printf("\n");
			scanf("%s",buff);
			sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
		}
	}

	close(sockfd);
}