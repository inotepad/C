#include <stdio.h>
#include <unistd.h>
void mulproc(int num,void *(*fn)(void *),void *arg);

void mulproc(int num,void *(*fn)(void *),void *arg)
{
	int i=0,pid;
	for(i=0;i<num_proc;i++)
	{
		if((pid=fork()) == 0)
		{
			fn(arg);
			exit(0);
		}
		else
			continue;
	}
	while(wait(NULL) != -1)
		;
}
