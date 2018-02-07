#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int pid;
	while((pid=fork())>=0)
		if(pid==0)
		{
			printf("pid=%ld\n",(long)getpid());
		}
		else if(pid>0)
		{
			printf("pid=%ld\n",(long)getpid());
		}
	if(pid<0)
		{
			fflush(stdout);
			printf("fork error\n");
			exit(-1);
		}
}
