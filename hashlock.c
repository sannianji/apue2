#include <stdlib.h>
#include <pthread.h>

#define NHASH 29
#define HASH (((unsigned long)id)%NHASH)

struct foo
{
	int f_count;
	int f_id;
	pthread_mutex_t f_lock;
	struct foo* f_next;
};
struct foo* fh[NHASH];
pthread_mutex_t hashlock=PTHRAD_MUTEX_INITIALIZER;

struct foo* alloc(int id)
{
	struct foo *fp;
	int idx;
	
	if((fp=malloc(sizeof(foo)))!=NULL)
	{
		fp->f_count=1;
		fp->f_id=id;
		
		if(pthread_mutex_init(&fp->f_lock,NULL)!=0)
		{
			free(fp);
			return NULL;
		}
	}
	
	idx=HASH(id);
	pthread_mutex_lock(&hashlock);
	fp->next=fh[idx];
	fh[idx]=fp;
	pthread_mutex_lock(&fp->f_lock);
	pthread_mutex_unlock(&hashlock);



	pthread_mutex_unlock(&fp->f_lock);
}

void f_hold(struct foo* fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}


struct foo* find(int id)
{
	struct foo *fp;
	
	pthread_mutex_lock(&hashlock);

	for(fp=fh[HASH(id)];fp!=NULL;fp=fp->next)
		if(fp->f_id==id)
			break;
	
	pthread_mutex_unlock(&hashlock);
	return(fp);
}


void foo_rele(struct foo *fp)
{
	struct foo *tfp;
	int idx;
	
	pthread_mutex_lock(&hashlock);
	if(fp->f_count==1)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		
		if(fp->f_count!=1)
		{
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}

		idx=HASH(id);
		tfp=fh[idx];
		if(tfp==fp)
			tfp=fp->f_next;
		else
		{
			while(tfp->f_next!=fp)
				tfp=tfp->f_next;
			tfp->f_next=fp->f_next;
		}
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else
	{
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}
