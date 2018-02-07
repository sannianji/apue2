#include "the_apue.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFSIZE 4096

int main(void)
{
	try{
	int n;
	char buf[BUFFSIZE];
	
	while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
		if(write(STDOUT_FILENO,buf,n)!=n)
			throw err_sys("write error");
	
	if(n<0)
		err_sys("read error");
	
	exit(0);
	}
	catch(err_sys& the_err)
	{
		cout<<the_err.output()<<endl;
		exit(-1);
	}
}
