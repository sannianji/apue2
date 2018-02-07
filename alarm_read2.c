#include "apue.h"
#include <setjmp.h>

static void sig_alrm(int signo);
static jmp_buf env_alrm;

int main(void)
{
	int n;
	char buff[MAXLINE];
	if(signal(SIGALRM,sig_alrm)==SIG_ERR)
		err_sys("signal (SIGALRM) error");
	if(setjmp(env_alrm)!=0)
		err_quit("read time out");
	else
	{
		alarm(10);
		if((n=read(STDIN_FILENO,buff,MAXLINE))<0)
			err_sys("read error");
		alarm(0);
		write(STDOUT_FILENO,buff,n);
		exit(0);
	}
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm,1);
}
