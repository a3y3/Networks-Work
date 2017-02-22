#include<stdio.h>
#include<string.h>
char str[30];
char toReplace[30];
char replacement[30];
void replaceTheString();
char new_string[30];
int main()
{
	printf("Enter a string\n");
	//char str[30];
	gets(str);
	printf("Enter the word you want to replace\n");
	//char toReplace[30];
	gets(toReplace);
	printf("Enter the replacement word\n");
	//char replacement[30];
	gets(replacement);
	int i = 0,l=strlen(str);
	replaceTheString();
	//printf("The new string is %s",str);
}
void replaceTheString()
{	
	int i = 0,temp_i=0,j=0,new_string_counter=0,x=0;;
	int l = strlen(str);
	for(i = 0;i < l;i++)
	{
		temp_i = i;
		for(j = 0;j<strlen(toReplace);j++)
		{	
			if(str[temp_i++]==toReplace[j])
			{
				if(j==(strlen(toReplace)-1))
				{
					//Substring successfully found. Replace now.
					for(x=0;x<i;x++)
					{
						new_string[new_string_counter++]=str[x];//String uptil substring. Check :D
					}
					for(x=0;x<strlen(replacement);x++)
					{
						new_string[new_string_counter++]=replacement[x];//:D
					}
					for(x=i+strlen(toReplace);x<strlen(str);x++)
					{
						new_string[new_string_counter++]=str[x];
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
}
			
	