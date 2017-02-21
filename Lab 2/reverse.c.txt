#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
	printf("Enter the sentence\n");
	char sentence[30];
	char rev[30];
	rev[0]='\0';
	gets(sentence);
	int l = strlen(sentence);
	printf("length is %d",l);
	int flag = 0;
	int i = 0;
	for(i = 0;i < l; i++)
	{
		rev[i] = sentence[l-1-i];
	}
	rev[i]='\0';
	for(i = 0;i < l;i++)
		printf("%s",&rev[i]);
}
