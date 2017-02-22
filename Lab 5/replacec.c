#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAX 100
char str[20], w[10], nstr[20], replaced[10], replacing[10];
void main()
{
int sockd, ret;
int rvdbytes, sentbytes;
struct sockaddr_in serveraddr;
char buff[MAX];
sockd=socket(AF_INET, SOCK_DGRAM, 0);
socklen_t len;
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
len = sizeof(serveraddr);
	printf("\nEnter a sentence: ");
	gets(str);
	sentbytes=sendto(sockd, str, sizeof(str), 0, (struct sockaddr*) &serveraddr, len);
	if(sentbytes==-1)
		close(sockd);
	
	printf("\nEnter word to be replaced: ");
	scanf("%s", replaced);
	sentbytes=sendto(sockd, replaced, sizeof(replaced), 0, (struct sockaddr*) &serveraddr, len);
	if(sentbytes==-1)
		close(sockd);

	printf("\nEnter replacing word: ");
	scanf("%s", replacing);
	sentbytes=sendto(sockd, replacing, sizeof(replacing), 0, (struct sockaddr*) &serveraddr, len);
	if(sentbytes==-1)
		close(sockd);


	rvdbytes=recvfrom(sockd, nstr, sizeof(nstr), 0, (struct sockaddr*) &serveraddr, &len);
	puts(nstr);
	printf("\n");

close(sockd);
}
