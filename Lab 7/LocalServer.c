#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

int main()
{
	struct TABLE
	{
		char host[10][20];
		char ip[10][20];
	};

	struct TABLE data;
	strcpy(data.host[0],"google.com");
	strcpy(data.ip[0],"172.16.16.16");
	strcpy(data.host[1],"yahoo.com");
	strcpy(data.ip[1],"173.16.19.16");
	strcpy(data.host[2],"msn.com");
	strcpy(data.ip[2],"174.16.16.16");

	int sockfd, newsockfd, retval; 
	int sig;
	socklen_t actlen;
	int rcvbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr, mainServerAddr;
	char buffer[100]; 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
		printf("\nSocket creation error");
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3333);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);

	
	retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(retval == -1)
	{
		printf("\nBind nahi hua.");
		close(sockfd);
	}
	
	actlen = sizeof(clientaddr);
	
	int pid;
	rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &actlen);
	printf("%s\n",buffer );
	//search now

	int i = 0, flag = 0;
	for(i = 0;i<3;i++){
		if(strcmp(buffer,data.host[i]) == 0){
			sentbytes = sendto(sockfd,data.ip[i],sizeof(data.ip[i]),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
			flag = 1;
		}
	}
	if(flag!=1)
	{
		mainServerAddr.sin_family = AF_INET;
		mainServerAddr.sin_port = htons(3334);
		mainServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		int sockFD2;
		int bind2 = bind(sockFD2, (struct sockaddr*)&mainServerAddr, sizeof(mainServerAddr));
		int len;
		len = sizeof(mainServerAddr);
		if(bind2 == -1)
		{
			printf("\nBind2 error");
			close(sockFD2);
		}
		sentbytes = sendto(sockFD2,buffer,sizeof(buffer),0,(struct sockaddr*)&mainServerAddr,sizeof(mainServerAddr));
		rcvbytes = recvfrom(sockFD2,buffer,sizeof(buffer),0,(struct sockaddr*)&mainServerAddr,&len);
		sentbytes = sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
		printf("Here\n");
	}
	close(sockfd);
}
