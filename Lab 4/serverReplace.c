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
	char username[50];
	recedbytes = recv(newsockfd, username, sizeof(username), 0);

	if (recedbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}
	char listUsername[50][50] = {"soham","aditya","pallavi","mehbooba"};
	int i = 0, flag = 0;
	for(i=0;i<4;i++)
	{
		if(strcmp(listUsername[i],username) == 0)
		{
			strcpy(buff,"Welcome! Please enter your password\n");
			sentbytes = send(newsockfd, buff, sizeof(buff),0);
			flag = 1;
		}
	}
	if(flag ==0)
	{
		printf("We do not have your username in our list. Please register.\n");
		close(sockfd);
		close(newsockfd);
	}	
	char listPassword[50][50] = {"root"};
	char password[90];
	recedbytes = recv(newsockfd, password, sizeof(password), 0);
	printf("The password is %s",password);
	char authMessage[90];
	int dbchoice;
	char title[50];
	char author[50];
	int accession_no;
	int total_pages;
	char publisher[50];
	if(strcmp(password,"root") == 0)
	{
		strcpy(authMessage, "Welcome to YourSQl. Type your command\n");
		sentbytes = send(newsockfd,authMessage,sizeof(authMessage),0);
		printf("%d\n",sentbytes );

		recedbytes = recv(newsockfd, title, sizeof(title), 0);
		printf("Title bytes recieved:%d\n", recedbytes);
		recedbytes = recv(newsockfd, author, sizeof(author), 0);
		printf("Author bytes recieved:%d\n", recedbytes);
		recedbytes = recv(newsockfd, author, sizeof(author), 0);
		recedbytes = recv(newsockfd, author, sizeof(author), 0);
		recedbytes = recv(newsockfd, &accession_no, sizeof(accession_no), 0);
		recedbytes = recv(newsockfd, &total_pages, sizeof(total_pages), 0);
		recedbytes = recv(newsockfd, publisher, sizeof(publisher), 0);


		printf("%s\n", title);		
		printf("%s\n", author);		
		printf("%d\n", accession_no);		
		printf("%d\n", total_pages);		
		printf("%s\n", publisher);
	}
	else
	{
		strcpy(buff,"Incorrect password.");
		sentbytes = send(newsockfd,buff,sizeof(buff),0);
		close(sockfd);
		close(newsockfd);
	}
	
	/*printf("Recieved sentence successfully:");
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
	char test[50];
	strcpy(test,"Replaced string is");
	sentbytes = send(newsockfd, test, sizeof(test),0);
	sentbytes = send(newsockfd, new_string, sizeof(new_string), 0);

	if (sentbytes == -1)
	{
		close(sockfd);
		close(newsockfd);
	}
*/
	close(sockfd);
	close(newsockfd);
}

