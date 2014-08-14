#include<sys/times.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void exec_time(void *(*fn)(void *),void *arg)
{
	clock_t start,end;
	long clktck=0;
	start=times(NULL);
	fn(arg);
	end=times(NULL);
	clktck=sysconf(_SC_CLK_TCK);
	printf("Time:%7.2fs\n",(end-start)/(double) clktck );
}
