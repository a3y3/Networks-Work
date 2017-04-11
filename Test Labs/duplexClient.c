#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 150

int sockfd=-1, pid=-1;
struct sockaddr_in serveraddr;
socklen_t actuallen=sizeof(serveraddr);
struct sockaddr* ptrToServer=(struct sockaddr *) &serveraddr;  //Typecast to suppress warning
char buff[MAXSIZE];

void quit();
void error(char *);
void doSend()
{
	printf("Send: ");
	scanf("%[^\n]%*c", buff);
	int sendStatus=sendto(sockfd, buff, sizeof(buff), 0, ptrToServer, actuallen);
	if(sendStatus==-1) error("Send Error!");
	if(strcmp(buff, "stop")==0)	quit();	
}
void doReceive()
{
	int recvStatus=recvfrom(sockfd, buff, sizeof(buff), 0, ptrToServer, &actuallen);
	if(recvStatus==-1) error("Receive Error!");
	printf("Server: %s\n", buff);
	if(strcmp(buff,"stop")==0) quit();
}

main()
{
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)	error("Socket Creation error!");
		
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("Client Ready\n");
	printf("-------------\n");
	doSend();
	
	pid=fork();
	if(pid<0) error("Fork Error!");
	
	while(1)
	{
		if(pid>0) //Parent
			doSend();
		else  //Child
			doReceive();	
	}
	quit();
}
void error(char *msg)
{	
	perror(NULL);
	printf("%s\n",msg);
	quit();
}
void quit()
{
	if(pid>0) kill(pid, SIGKILL);
	else if(pid==0) kill(getppid(), SIGKILL);
	if(sockfd!=-1) close(sockfd);
	puts("Client Exiting");
	exit(0);
}

