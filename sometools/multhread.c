#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void multhread(int num,void *(*fn)(void *),void *arg);
void makethread(void *(*fn)(void *),void *arg);

void multhread(int num,void *(*fn)(void *),void *arg)
{
	int i=0;
	for(i=0;i<num;i++)
		makethread(fn,arg);
}
void makethread(void *(*fn)(void *),void *arg)
{
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&tid,&attr,fn,arg);
	pthread_attr_destroy(&attr);
}
