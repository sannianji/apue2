#include "apue.h"
int main()
{
	printf("real uid=%d,effective uid=%d\n",getuid(),getpid());
	exit(0);
}
