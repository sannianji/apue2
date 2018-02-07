#ifndef __THE_APUE_H__
#define __THE_APUE_H__
#include <string>
#include <iostream>
#include <fcntl.h>
#include <cstdlib>
using namespace std;
class err_sys
{
public:
	err_sys():str("system error"){}
	err_sys(const char* c):str(c){}
	string output() const {return str;}
private:
	string str;
};
class err_quit
{
public:
	err_quit():str("error quit"){}
	err_quit(const char* c):str(c){}
	string output() const {return str;}
private:
	string str;
};
class err_dump
{
public:
	err_dump():str("error dump"){}
	err_dump(const char* c):str(c){}
	string output() const {return str;}
private:
	string str;
};
class err_ret
{
public:
	err_ret():str("the ret error"){}
	err_ret(const char *c):str(c){}
	string output()const {return str;}
private:
	string str;
};

void set_f1(int fd,int flags)
{
	try{
		int val;
		
		if((val=fcntl(fd,F_GETFL,0))<0)
			throw err_sys("fcntl F_GETFL error");
	
		val|=flags;
	
		if(fcntl(fd,F_SETFL,val)<0)
			throw err_sys("fcntl F_SETFL error");
	}catch(err_sys& the_err)
	{
		cout<<the_err.output()<<endl;
		exit(0);
	}
}
void set_f2(int fd,int flags)
{
	try{
		int val;
	
		if((val=fcntl(fd,F_GETFL,0))<0)
			throw err_sys("fcntl F_GETFL error");
	
		val&=~flags;
	
		if(fcntl(fd,F_SETFL,val)<0)
			throw err_sys("fcntl F_SETFL error");
	}catch(err_sys& the_err)
	{
		cout<<the_err.output()<<endl;
		exit(0);
	}
}
#endif
