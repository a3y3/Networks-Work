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
int sockd, ret;
int rvdbytes, sentbytes;
struct sockaddr_in serveraddr;
char buff[MAX];
socklen_t actlen;
sockd=socket(AF_INET, SOCK_DGRAM, 0);

if(sockd==-1)
	printf("\nSocket creation error");

printf("%i", sockd);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
/*ret=connect(sockd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

if(ret==-1)
	printf("\nConnection error");
*/
actlen=sizeof(serveraddr);
while(1)
{
	printf("\nEnter the text\n");
	scanf("%s",buff);
	sentbytes=sendto(sockd, buff, sizeof(buff), 0, (struct sockaddr*)&serveraddr, actlen);

	if(sentbytes==-1)
		close(sockd);
	if(strcmp(buff,"stop")==0)
		break;
	rvdbytes=recvfrom(sockd, buff, sizeof(buff), 0, (struct sockaddr*)&serveraddr, &actlen);
	puts(buff);
	printf("\n");
}
close(sockd);
}
