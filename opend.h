#include "apue.h"
#include <errno.h>

#define CL_OPEN "open"

extern char errmsg[];
extern int oflag;
extern char *pathname;

int cli_arg(int,char **);
void hadle_request(char *,int,int);
