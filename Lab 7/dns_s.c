#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#define max 50
int flag = 0;

struct dnsTable{

	char name[max];
	char ip[max];
};

int main()
{
	int sockfd,newsockfd,k;
	socklen_t actuallen;
	int retval;
	size_t leng;
	char c;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr, mainserveraddr;
	char buff[max], temp[max];
	int a=0;
	struct dnsTable dt = {"www.google.com", "14.12.54.221"};
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		printf("\n Socket creation error");
		exit(0);
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3391);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_port=htons(3392);
	clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("\n Binding error");
		close(sockfd);
	 	exit(0);
	}
	actuallen=sizeof(clientaddr);
	do{
        retval=recvfrom(sockfd,temp,sizeof(temp),0,(struct sockaddr *)&clientaddr,&actuallen);
        puts(temp);
        if(retval==-1)
		{
			close(sockfd);
			exit(0);
		}
        if(strcmp(temp, "stop") == 0)
        {
            puts("Stopping");
            close(sockfd);
            close(newsockfd);    
        }
        else if(strcmp(temp, "www.google.com") == 0)
        {
            strcpy(buff, dt.ip);
            puts(buff);
            retval=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&clientaddr,actuallen);
       	}
       	else if(strcmp(temp, "www.yahoo.com") == 0)
       	{
       		newsockfd=socket(AF_INET,SOCK_DGRAM,0);
       		mainserveraddr.sin_family=AF_INET;
			mainserveraddr.sin_port=htons(3390);
			mainserveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
			retval=bind(sockfd,(struct sockaddr *)&mainserveraddr,sizeof(mainserveraddr));
			actuallen=sizeof(mainserveraddr);
			retval=sendto(newsockfd,temp,sizeof(temp),0,(struct sockaddr *)&mainserveraddr,actuallen);
			retval=recvfrom(newsockfd,temp,sizeof(temp),0,(struct sockaddr *)&mainserveraddr,&actuallen);
			actuallen=sizeof(clientaddr);
			retval=sendto(sockfd,temp,sizeof(temp),0,(struct sockaddr *)&clientaddr,actuallen);
	    }
    }while(strcmp(buff, "stop") != 0);
	close(sockfd);
}