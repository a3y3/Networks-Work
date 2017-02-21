#include<iostream.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
int main()
{
	int sockfd;
	struct sockaddr_in serverAddress;
	char string[30];
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("Error creating socket");
		exit(0);
	}
	serverAddress.sin_family = AF_INET;	//?
	serverAddress.sin_port = htons(3388);	//where the f did this come from?
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	int connection;
	connection = connect(sockfd,(const struct sockaddr)&serverAddress,sizeof(serverAddress));
	if(connection == -1)
	{
		printf("Connection error!");
		exit(0);
	}
	//printf("Enter text");
	
