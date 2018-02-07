#include "apue.h"
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int i,fd;
	struct timespec times[2];
	struct stat statbuf;
	for(i=1;i<argc;++i)
	{
		if(stat(argv[i],&statbuf)<0)
		{
			err_ret("%s: stat error",argv[1]);
			continue;
		}
		if((open(argv[i],O_RDWR|O_TRUNC))<0)
		{
			err_ret("%s: open error",argv[1]);
			continue;
		}

		times[0]=statbuf.st_atim;
		times[1]=statbuf.st_mtim;
	
		if(futimens(fd,times)<0)
			err_ret("%s: futimens error",argv[1]);
		close(fd);
	}
	exit(0);
}
