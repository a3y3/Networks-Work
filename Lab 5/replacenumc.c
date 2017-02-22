#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAX 100
//char str[20], w[10], nstr[20], replaced[10], replacing[10];
int n, a[10], key;
void main()
{
int sockd, ret, i;
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
len=sizeof(serveraddr);
	printf("\nEnter no. of elements: ");
	scanf("%d", &n);
	int sn=htonl(n);
	sentbytes=sendto(sockd, &sn, sizeof(sn), 0, (struct sockaddr*) &serveraddr, len);
	if(sentbytes==-1)
		close(sockd);
		
	printf("\nEnter elements:\n");
	for(i=0; i<n; i++)
		scanf("%d ", &a[i]);
	printf("\nEnter key: ");	
	sentbytes=sendto(sockd, a, sizeof(a), 0, (struct sockaddr*) &serveraddr, len);
	if(sentbytes==-1)
		close(sockd);


	scanf("%d", &key);
	int skey=htonl(key);
	sentbytes=sendto(sockd, &skey, sizeof(skey), 0, (struct sockaddr*) &serveraddr, len);
	if(sentbytes==-1)
		close(sockd);


	rvdbytes=recvfrom(sockd, buff, sizeof(buff), 0, (struct sockaddr*) &serveraddr, &len);
	puts(buff);
	printf("\n");

close(sockd);
}
