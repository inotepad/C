#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *handle_quit_enter(void *);
void *handle_exit_chk(void *);
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;
void *handle_quit_enter(void *a)
{
	printf("Press Enter to Quit\n");
	if(getchar())
	{
		printf("Bye\n");
		exit(0);
	}
}
void *handle_exit_chk(void *a)
{
	while(act_thread >0)
		sleep(1);
	exit(0);
}
void *handle_exit_chk(void *a)
{
	int num=0;

	do
	{
		pthread_mutex_lock(&counter_lock);
		num=act_thread;
		pthread_mutex_unlock(&counter_lock);
		if(num)
			sleep(1);
		else
			break;
	}while(1);
	exit(0);
}
