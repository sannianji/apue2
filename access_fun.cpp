#include "the_apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>
int main(int argc,char* argv[])
{
try{
	if(argc!=2)
		throw err_quit("usage: a.out <pathname>");
	cout<<"hello world"<<endl;
	return 0;
	if(access(argv[1],R_OK)<0)
	{
		char *c="access error for ";
		copy(argv[1],argv[1]+strlen(argv[1]),c+strlen(c));
		throw err_ret(c);
	}
	else
		printf("read access OK\n");
	if(open(argv[1],O_RDONLY)<0)
	{
		char *c="open error for ";
		copy(argv[1],argv[1]+strlen(argv[1]),c+strlen(c));
		throw err_ret(c);
	}
	else
		printf("open for reading OK\n");
	exit(0);
}
catch(err_quit& the_err)
{
	cout<<the_err.output()<<endl;
}
catch(err_ret& the_err)
{
	cout<<the_err.output()<<endl;
	exit(-1);
}
}
