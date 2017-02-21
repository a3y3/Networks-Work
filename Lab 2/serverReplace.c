#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

int main()
{
	int sockfd, newsockfd, retval;
	socklen_t actuallen;
	int recedbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr;

	char buff[MAXSIZE];
	int a = 0;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1)
	{
		printf("\nSocket creation error");
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(3388);
	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
	retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == 1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval = listen(sockfd, 1);
	if (retval == -1)
	{
		close(sockfd);
	}

	actuallen = sizeof(clientaddr);
	newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);


	if (newsockfd == -1)
	{
		close(sockfd);
	}
	recedbytes = recv(newsockfd, buff, sizeof(buff), 0);

	if (recedbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}

	printf("Recieved sentence successfully:");
	printf("%s\n",buff);
	char replacement[50];
	char toReplace[50];
	char new_string[50];
	
	recedbytes = recv(newsockfd, toReplace, sizeof(toReplace), 0);
	if (recedbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}
	printf("Recieved toReplace successfully:");
	printf("%s\n",toReplace);
	recedbytes = recv(newsockfd, replacement, sizeof(replacement), 0);

	if (recedbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}
	printf("Recieved replacement successfully:");
	printf("%s",replacement);
	
	int i = 0,temp_i=0,j=0,new_string_counter=0,x=0;

	int l = strlen(buff);

	for(i = 0;i < l;i++)

	{

		temp_i = i;

		for(j = 0;j<strlen(toReplace);j++)

		{	

			if(buff[temp_i++]==toReplace[j])

			{

				if(j==(strlen(toReplace)-1))

				{

					//Substring successfully found. Replace now.

					for(x=0;x<i;x++)

					{

						new_string[new_string_counter++]=buff[x];//String uptil substring. Check :D

					}

					for(x=0;x<strlen(replacement);x++)

					{

						new_string[new_string_counter++]=replacement[x];//:D

					}

					for(x=i+strlen(toReplace);x<strlen(buff);x++)

					{

						new_string[new_string_counter++]=buff[x];

					}

					printf("After replacement, string looks like this:%s\n",new_string);

				}

			}

			else

			{

				break;

			}
		}
	}


	printf("\n");
	string test[50];
	strcpy(test,"Replaced string is");
	sendbytes = send(newsockfd, test, sizeof(test),0);
	sentbytes = send(newsockfd, new_string, sizeof(new_string), 0);

	if (sentbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}

	close(sockfd);
	close(newsockfd);
}

