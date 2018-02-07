#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;
char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

class err_sys
{
public:
	err_sys():str("system error"){}
	err_sys(const char* c):str(c){}
	string output() const { return str; }
private:
	string str;
};
int main(void)
{
	int fd;
	try{
	if((fd=creat("file.hole",S_IRUSR|S_IWUSR|S_IXUSR))<0)
		throw err_sys("creat error");

	if(write(fd,buf1,10)!=10)
		throw err_sys("buf1 write error");
	
	if(lseek(fd,16384,SEEK_SET)==-1)
		throw err_sys("lseek error");
	
	if(write(fd,buf2,10)!=10)
		throw err_sys("buf2,write error");
	}
	catch(err_sys& the_err)
	{
		cout<<the_err.output()<<endl;
		exit(-1);
	}
}
