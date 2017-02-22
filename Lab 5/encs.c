#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAX 100
char rev[10], buff[30];
int i, j, l, flag=0;
int main()
{
	int encrypted[30];
	int sockd, ret;
	socklen_t len;
	int rvdbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr;
	char buff[MAX];
	int a=0;
	sockd=socket(AF_INET, SOCK_DGRAM, 0);

	if(sockd==-1)
		printf("\nSocket creation error");

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(4588);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	ret=bind(sockd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

	if(ret==-1)
	{
		printf("\nBinding error");
		close(sockd);
	}

	/*(ret=listen(sockd,1);

	if(ret==-1)
		close(sockd);
*/
	len=sizeof(clientaddr);
/*	newsockd=accept(sockd,(struct sockaddr*)&clientaddr, &len);

	if(newsockd==-1)
		close(sockd);
*/
	rvdbytes=recvfrom(sockd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, &len);

	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}
	puts(buff);
	printf("\n");
	
	flag=0;
	l= strlen(buff);
	for(i=0; i<l; i++)
	{
		encrypted[i]= (int)(buff[i] - 64);
		//decrypted[i]= encrypted[i] + 64;
	}
	for(i = 0;i <l; i++)
		printf("%d ",encrypted[i]);
	sentbytes=sendto(sockd, encrypted, sizeof(encrypted), 0, (struct sockaddr*)&clientaddr, len);

	if(sentbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}
	
	//printf("Closing socket...");
	close(sockd);
	//close(newsockd);
}
	
