#include "apue.h"

static void sig_usr(int);

int main(void)
{
	setvbuf(stdout,NULL,_IONBF,0);
	printf("this is the handle_sig.c\n");
	if(signal(SIGUSR1,sig_usr)==SIG_ERR)
		err_sys("signal (SIGUSR1) error");
	if(signal(SIGUSR2,sig_usr)==SIG_ERR)
		err_sys("signal (SIGUSR2) error");
	for(;;)
		pause();
}

static void sig_usr(int signo)
{
	if(signo==SIGUSR1)
		printf("SIGUSR1 received\n");
	else if(signo==SIGUSR2)
		printf("SIGUSR2 received\n");
	else
		err_dump("received signal %d\n",signo);
}
