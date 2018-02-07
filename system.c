#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include "apue.h"
int system(const char *cmdstring)
{
	pid_t pid;
	int status;
	if(cmdstring==NULL)
		return (1);
	
	if((pid=fork())<0)
		status=-1;
	else if(pid==0)
	{
		execlp("/bin/sh","sh","-C",cmdstring,(char *)0);
		_exit(127);
	}
	else
	{
		while(waitpid(pid,&status,0)<0)
		{
			if(errno!=EINTR)
			{
				status=-1;
				break;
			}
		}
	}
	
	return (status);
}

static void sig_int(int signo)
{
	printf("caught SIGINT\n");
}

static void sig_chld(int signo)
{
	printf("caught SIGCHLD\n");
}

int main(void)
{
	if(signal(SIGCHLD,sig_chld)==SIG_ERR)
		err_sys("signal (SIGCHLD) error");
	if(signal(SIGINT,sig_int)==SIG_ERR)
		err_sys("signal (SIGCHLD) error");
	if(system("/bin/ed")<0)
		err_sys("system() error");
	exit(0);
}
