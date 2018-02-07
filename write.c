#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	int i;
	char buf[]="helloworld";
	for(i=0;i<10000000;++i)
		if(write(STDOUT_FILENO,buf,sizeof(buf))!=sizeof(buf))
		{
			printf("write error");
			exit(-1);
		}
	return 0;
}
