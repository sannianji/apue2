#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


static pid_t *childpid=NULL;

static int maxfd;

FILE* popen(const char *cmdstring,const char *type)
{
	int i;
	int pfd[2];
	pid_t pid;
	FILE *fp;
	
	if((type[0]!='r'&&type[0]!='w')||type[1]!=0)
	{
		errno=EINVAL;
		return (NULL);
	}
	
	if(childpid==NULL)
	{
		maxfd=open_max();
		if((childpid=calloc(maxfd,sizeof(pid_t)))==NULL)
			return (NULL);
	}

	if(pipe(pfd)<0)
		return (NULL);
	if(pfd[0]>=maxfd||pfd[1]>=maxfd)
	{
		close(pfd[0]);
		close(pfd[1]);
		errno=EMFILE;
		return (NULL);
	}

	if((pid=fork())<0)
		return NULL;
	else if(pid==0)//child
	{
		if(*type=='r')
		{
			close(pfd[0]);
			if(pfd[1]!=STDOUT_FILENO)
			{
				dup2(pfd[1],STDOUT_FILENO);
				close(pfd[1]);
			}
		}
		else
		{
			close(pfd[1]);
			if(pfd[0]!=STDIN_FILENO)
			{
				dup2(pfd[0],STDIN_FILENO);
				close(pfd[0]);
			}
		}
		for(i=0;i<maxfd;++i)
			if(childpid[i]>0)
				close(i);

		execl("/bin/bash","bash","-c",cmdstring,(char *)0);
		_exit(127);
	}

	//parent
	if(*type=='r')
	{
		close(pfd[1]);
		if((fp=fdopen(pfd[0],type))==NULL)
			return NULL;
	}
	else
	{
		close(pfd[0]);
		if((fp=fdopen(pfd[1],type))==NULL)
			return NULL;
	}
	childpid[fileno(fp)]=pid;
	return (fp);
}
