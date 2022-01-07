#include "headers.h"
 void echo(int j,char *arr[])
{
	int i=1;
	char *ch;
	while(arr[i]!=NULL)
	{
		ch=arr[i];
		if(*ch=='$'&&*(ch+1)=='?')
		{
		
	
		statusCommand(j);
			ch++;
			
			
		}else
		{
			printf("%s ",arr[i]);
		}
		i++;
	}
	printf("\n");
	return;
}
