#include	<stdio.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<netdb.h>
#define   HOSTLEN  256
int main(int argc, const char *argv[])
{
	struct	hostent		*hp;   /* this is part of our    */
	char	hostname[HOSTLEN];     /* address 	         */
	gethostname(hostname, HOSTLEN);         /* where am I ?         */
    printf("HostName:%s\n",hostname);
	hp = gethostbyname(hostname);           /* get info about host  */
    if((void *)hp == NULL)
        printf("NULL!\n");
    else
        printf("OK\n");
    return 0;
}
