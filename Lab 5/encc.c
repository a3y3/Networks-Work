#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAX 100

void main()
{
	int i = 0;
	int l;
	int encrypted[10];
	int sockd, ret;
	int rvdbytes, sentbytes;
	struct sockaddr_in serveraddr;
	char buff[MAX];
	sockd=socket(AF_INET, SOCK_DGRAM, 0);

	if(sockd==-1)
		printf("\nSocket creation error");

	printf("%i", sockd);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(4588);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	/*ret=connect(sockd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

	if(ret==-1)
		printf("\nConnection error");
*/
	socklen_t len=sizeof(serveraddr);
	printf("\nEnter the text\n");
	gets(buff);
	sentbytes=sendto(sockd, buff, sizeof(buff), 0, (struct sockaddr*) &serveraddr, len);

	if(sentbytes==-1)
		close(sockd);
	
	rvdbytes=recvfrom(sockd, encrypted, sizeof(encrypted), 0, (struct sockaddr*) &serveraddr, &len);
	l = strlen(buff);
	printf("The size of l is %d",l);
	printf("\nThe encrypted string is: ");
	for(i = 0;i <l; i++)
		printf("%d ",encrypted[i]);
	//puts(encrypted);
	printf("\n");

	close(sockd);
}
