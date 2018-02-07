#include <stdio.h>
#include <unistd.h>
#include <signal.h>
static void sig_usr(int);
int main()
{
	if(signal(SIGUSR1,sig_usr)==SIG_ERR)
		return -1;
	printf("helloworld\n");
	pause();
}

static void sig_usr(int signo)
{
	printf("signal SIGUSR1 received\n");
}
