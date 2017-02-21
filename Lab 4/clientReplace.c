#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 50

main()
{
	int sockfd,retval;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	char buff[MAXSIZE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
	}
	printf("%i",sockfd);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection error");
	}
	printf("Enter your username\n");
	char username[50];
	scanf("%s",username);


	sentbytes=send(sockfd,username,sizeof(username),0);			//username sent

	if(sentbytes==-1)
	{
		printf("username can't be sent");
		close(sockfd);
	}
	
	
	recedbytes=recv(sockfd,buff,sizeof(buff),0);		//message recieved
	printf("%s",buff);

	char password[50];
	scanf("%s",password);
	sentbytes=send(sockfd,password,sizeof(password),0);			//password sent

	if(sentbytes==-1)
	{
		printf("password can't be sent");
		close(sockfd);
	}
	printf("HELLO\n");
	printf("HII\n");
	char auth[50];
	recedbytes=recv(sockfd,auth,sizeof(auth),0);		//password authentication recieved
	recedbytes=recv(sockfd,auth,sizeof(auth),0);
	printf("Value is %d\n", recedbytes);
	printf("%s\n",auth);
	if(strcmp(auth,"Incorrect password.") == 0)
	{
		close(sockfd);
	}
	else
	{
		printf("\n\n1.insert into books(title, author, accession_no, total_pages, publisher.) values ");
		printf("\n2.delete from books where title like ");
		printf("\n3.select * from books where title like  ");
		printf("\n4.select title from books where title like ");
		printf("\n5.Exit");
		int dbchoice;
		char title[50];
		char author[50];
		int accession_no;
		int total_pages;
		char publisher[50];
		dbchoice = scanf("%d",&dbchoice);
		if(dbchoice == 1)
		{
			printf("%s\n", "title:");
			scanf("%s",title);
			printf("%s\n", "author:");
			scanf("%s",author);
			printf("%s\n", "accession_no:");
			scanf("%d",&accession_no);
			printf("%s\n", "total_pages:");
			scanf("%d",&total_pages);
			printf("%s\n", "publisher:");
			scanf("%s",publisher);

			sentbytes=send(sockfd,title,sizeof(title),0);
			printf("Title bytes sent%d\n", sentbytes);	
			sentbytes=send(sockfd,author,sizeof(author),0);	
			printf("author bytes sent%d\n", sentbytes);
			sentbytes=send(sockfd,&accession_no,sizeof(accession_no),0);	
			sentbytes=send(sockfd,&total_pages,sizeof(total_pages),0);	
			sentbytes=send(sockfd,publisher,sizeof(publisher),0);	
		}
		if(dbchoice == 2)
		{
			scanf("%s",title);
		}
		if(dbchoice == 3)
		{
			scanf("%s",title);
		}
		if(dbchoice ==4)
		{
			scanf("%s",title);
		}
		if(dbchoice ==5)
		{
			close(sockfd);
			exit(1);
		}
	}
	close(sockfd); 
}
