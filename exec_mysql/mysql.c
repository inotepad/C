
void exec_time(char *path)
{
	clock_t start,end;
	long clktck=0;
	start=times(NULL);
	exec_mysql(path);
	end=times(NULL);
	clktck=sysconf(_SC_CLK_TCK);
	printf("Time:%7.2fs\n",(end-start)/(double) clktck );
}

void exec_mysql(char *path)
{
    FILE *fp;
    int postion=0,len=0;
    char *query=NULL;
    char *buf=NULL;
    if( (fp=fopen(path,"r")) == NULL)
	{
		fprintf(stderr,"File %s doesn't exist\n",path);
		exit(1);
	}
    if( (buf=(char *) malloc(BUFSIZ)) == NULL)
		exit(1);
	memset(buf,'\0',BUFSIZ);
    if( (query=(char *) malloc(BUFSIZ)) == NULL)
		exit(1);
	memset(query,'\0',BUFSIZ);
    while( fgets(buf,BUFSIZ,fp) )
    {
		len=strlen(buf);
        postion=len-2;
        if(buf[postion] == ';')
        {
            buf[postion]='\0';
            strcpy(query,buf);
		}
        else
        {
            fputs(buf,stderr);
        }
    }
	free(buf);
	free(query);
    fclose(fp);
}
