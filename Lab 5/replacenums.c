#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAX 100
int i, l, j=0, k=0;
//char str[20], w[10], nstr[20], replaced[10], replacing[10];
int a[10], n, key; 
void main()
{
int sockd, newsockd, ret;
socklen_t len;
int rvdbytes, sentbytes;
struct sockaddr_in serveraddr, clientaddr;
char buff[MAX];
strcpy(buff,"Not Found!");
int a[50];
sockd=socket(AF_INET, SOCK_DGRAM, 0);

if(sockd==-1)
	printf("\nSocket creation error");

serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
ret=bind(sockd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

if(ret==-1)
{
	printf("\nBinding error");
	close(sockd);
}

/*ret=listen(sockd,1);

if(ret==-1)
	close(sockd);
*/
len=sizeof(clientaddr);
/*newsockd=accept(sockd,(struct sockaddr*)&clientaddr, &len);

if(newsockd==-1)
	close(sockd);
*/
	rvdbytes=recvfrom(sockd, &n, sizeof(n), 0, (struct sockaddr*)&clientaddr, &len);
	int rn=ntohl(n);
	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}
	rvdbytes=recvfrom(sockd, a, sizeof(a), 0, (struct sockaddr*)&clientaddr, &len);

	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}
	rvdbytes=recvfrom(sockd, &key, sizeof(key), 0, (struct sockaddr*)&clientaddr, &len);
	int rkey=ntohl(key);
	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}

	for(i=0; i<rn; i++)
	{
		if(a[i]==rkey)
		{
			strcpy(buff,"Found");
		}
	}
	sentbytes=sendto(sockd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, len);

	if(sentbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}

close(sockd);
//close(newsockd);
}
	
