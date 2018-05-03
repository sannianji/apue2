#include"apue.h"
#include <sys/wait.h>
static void sig_cld(int);
int main()
{
	pid_t pid;
	if(signal(SIGCLD,sig_cld)==SIG_ERR)
		perror("signal error");
	if((pid=fork())<0)
		perror("fork error");
	if(pid==0)//child
	{
		sleep(2);
		_exit(0);
	}
	
	pause();
	return 0;
}

void sig_cld(int signo)
{
	int status;
	pid_t pid;
	if(signal(SIGCLD,sig_cld)==SIG_ERR)
		perror("signal error");
	printf("SIGCLD received\n");
	if((pid=wait(&status))<0)
		perror("wait error");

	printf("pid = %ld\n",(long)pid);
	
}
