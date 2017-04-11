#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 150

int sockfd=-1, newsockfd=-1, pid=-1;
struct sockaddr_in serveraddr, clientaddr;
socklen_t actuallen=sizeof(serveraddr);
struct sockaddr* ptrToClient=(struct sockaddr *) &clientaddr;  //Typecast to suppress warning
char buff[MAXSIZE];

void quit();
void error(char *);
void doSend() 
{
	printf("Send: ");
	scanf("%[^\n]%*c", buff);
	int sendStatus=sendto(sockfd, buff, sizeof(buff), 0, ptrToClient, actuallen);
	if(sendStatus==-1)	error("Send Error!");
	if(strcmp(buff, "stop")==0) quit();
}
void doReceive() 
{
	int recvStatus=recvfrom(sockfd, buff, sizeof(buff), 0, ptrToClient, &actuallen);
	if(recvStatus==-1)	error("Receive Error!");
	printf("Client: %s\n", buff);
	if(strcmp(buff,"stop")==0) quit();
}

main()
{	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1) error("Socket creation error!");
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);

	int retval=bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(retval==1) error("Binding error");
	
	printf("Waiting for client\n");
	printf("-------------\n");
	doReceive();
	
	pid=fork();
	if(pid<0) error("Fork Error!");
	
	while(1)
	{
		if(pid>0) //Parent
			doReceive();
		else  //Child
			doSend();		
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
	if(sockfd!=-1)	close(sockfd);
	if(newsockfd!=-1) close(newsockfd);
	puts("Server Exiting");
	exit(0);
}

