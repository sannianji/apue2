#include "apue.h"
#include <fcntl.h>
int main()
{
	creat("tempfile",S_IRUSR|S_IWUSR);
}
