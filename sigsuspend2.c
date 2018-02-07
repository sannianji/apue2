#include "apue.h"
#include <pthread.h>
volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
	if(signo==SIGINT)
	{
		if(signal(SIGINT,sig_int)==SIG_ERR)
			err_sys("signal SIGINT error");
		printf("\ninterrupt\n");
	}
	else if(signo==SIGQUIT)
		quitflag=1;
}
static void* thr_fun(void* arg)
{
	while(1)
		raise(SIGINT);
}
int main(void)
{
	pthread_t tid;
	sigset_t newmask,oldmask,zeromask;
	
	if(signal(SIGINT,sig_int)==SIG_ERR)
		err_sys("signal SIGINT error");
	if(signal(SIGQUIT,sig_int)==SIG_ERR)
		err_sys("signal SIGQUIT error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);
	
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
		err_sys("sigprocmask SIG_BLOCK error");
	pthread_create(&tid,NULL,thr_fun,(void *)1);
	pthread_detach(tid);
	while(quitflag==0)
		sigsuspend(&zeromask);
//	pause();
	quitflag=0;
//	pause();
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
		err_sys("sigprocmask SIG_SETMASK error");
	
	exit(0);
}
