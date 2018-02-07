#include "the_apue.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
try{
	int val;
	if(argc!=2)
		throw err_quit("usage: a.out <descriptor#>");
	
	if((val=fcntl(atoi(argv[1]),F_GETFL,0))<0)
	{
		char *c="fcntl error for fd ";
		c+=atoi(argv[1]);
		throw err_sys(c);
	}

	switch(val&O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");
			break;
		
		case O_WRONLY:
			printf("write only");
			break;
		
		case O_RDWR:
			printf("read & write");
			break;
	
		default:
			err_dump("unknown access mode");
	}

	if(val&O_APPEND)
		printf(",append");
	if(val&O_NONBLOCK)
		printf(",nonblocking");
	if(val&O_SYNC)
		printf(",synchonous writes");

#if !defined(_POSIX_C_SOURCE)&&defined(O_FSYNC)&&(O_FSYNC!=O_SYNC)
	if(val&O_FSYNC)
		printf(",synchronous writes");
#endif
	
	putchar('\n');
	exit(0);
}
catch(err_sys& the_err)
{
	cout<<the_err.output()<<endl;
	exit(-1);
}
catch(err_quit& the_err)
{
	cout<<the_err.output()<<endl;
	exit(-1);
}
catch(err_dump& the_err)
{
	cout<<the_err.output()<<endl;
	exit(-1);
}
}
