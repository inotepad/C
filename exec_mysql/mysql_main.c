#include "mysql.h"

int main(int argc,char *argv[])
{
	if(argc == 1)
	{
		fprintf(stderr,"error\n");
		exit(1);
	}
	while( --argc)
	{
		exec_time(* ++argv);
	}
	return 0;
}
