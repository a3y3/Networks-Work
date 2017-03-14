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
	struct dnsTable dt = {"www.yahoo.com", "67.112.54.221"};
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		printf("\n Socket creation error");
		exit(0);
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3391);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	mainserveraddr.sin_family=AF_INET;
	mainserveraddr.sin_port=htons(3390);
	mainserveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=bind(sockfd,(struct sockaddr *)&mainserveraddr,sizeof(mainserveraddr));
	if(retval==-1)
	{
		printf("\n Binding error");
		close(sockfd);
	 	exit(0);
	}
	actuallen=sizeof(serveraddr);
	do{
        retval=recvfrom(sockfd,temp,sizeof(temp),0,(struct sockaddr *)&serveraddr,&actuallen);
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
        else if(strcmp(temp, "www.yahoo.com") == 0)
        {
            strcpy(buff, dt.ip);
            retval=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&serveraddr,actuallen);
       	}
       	else
       	{
       		strcpy(buff, "Not found");
			retval=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&clientaddr,actuallen);
	    }
    }while(strcmp(buff, "stop") != 0);
	close(sockfd);
}