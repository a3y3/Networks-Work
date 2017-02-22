#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAX 100
int i, l, j=0, k=0;
char str[20], w[10], nstr[20], replaced[10], replacing[10];
void main()
{
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

*/	rvdbytes=recvfrom(sockd, str, sizeof(str), 0, (struct sockaddr*)&clientaddr, &len);

	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}
	rvdbytes=recvfrom(sockd, replaced, sizeof(replaced), 0, (struct sockaddr*)&clientaddr, &len);

	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}
	rvdbytes=recvfrom(sockd, replacing, sizeof(replacing), 0, (struct sockaddr*)&clientaddr, &len);

	if(rvdbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}

//	puts(buff);
	printf("\n");
	strcat(str," ");
	l= strlen(str);
	for(i=0; i<l; i++)
	{
		if(str[i] != ' ')
		{
			w[k++] = str[i];
			//pos = i;
		}
		else
		{
			w[k]='\0';
			printf("%s \n", w);
			if(strcmp(w,replaced) == 0)
			{	
				k=0;
				while(k < strlen(replacing)) 
				nstr[j++] = replacing[k++];
			}
			else
		 	{	
				k=0;
				while(k < strlen(replaced)) 
				nstr[j++] = w[k++];
			}
			w[0] ='\0';
			k=0;
			nstr[j++]=' ';
		 }
	}
	nstr[j]='\0';
	//printf("\nThe new string is: %s", nstr);
	strcpy(buff,nstr);
	sentbytes=sendto(sockd, nstr, sizeof(nstr), 0, (struct sockaddr*)&clientaddr, len);

	if(sentbytes==-1)
	{
		close(sockd);
		//close(newsockd);
	}

close(sockd);
//close(newsockd);
}
	
