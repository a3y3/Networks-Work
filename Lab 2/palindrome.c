#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char sentence[30];
	do
	{
		printf("Enter thee sentence!\n");
		gets(sentence);
		int flag=0,i=0;
		for(i=0; i<strlen(sentence);i++)
		{
			if(sentence[i]!=sentence[strlen(sentence)-1-i])
			{
				flag =1;
			}
			else
				continue;
		}
		if(flag==0)
		{
			printf("Palindrome\n");
		}
		else
			printf("Not palindrome\n");
	}
	while(strcmp(sentence,"end")!=0);
}
