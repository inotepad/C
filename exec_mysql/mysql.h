#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mysql/mysql.h>
#include<sys/times.h>
#include<malloc.h>
#include<string.h>

#define IPADDR         "localhost"
#define PASSWD         "123"
/*
#define IPADDR         "192.168.1.1"
#define PASSWD         "123"
*/
#define USER           "root"
#define DATABASE       "test"
#define safe(C)        if(C)\
	{\
		fprintf(stderr,"%s\n",mysql_error(conn));\
		exit(1);\
	}

void exec_mysql(char *path);
void exec_time(char *path);

