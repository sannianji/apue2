#include "apue.h"
int send_err(int fd,int errcode,const char *msg)
{
	int n;
	if((n=strlen(msg))>0)
		if(writen(fd,msg,n)!=n)
		
}
