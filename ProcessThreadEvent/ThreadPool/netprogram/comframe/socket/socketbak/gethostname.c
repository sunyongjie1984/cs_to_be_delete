#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>

main(int argc,char* argv[])
{
    struct sockaddr_in addr;
    struct hostent *he;
    char  **alias;
    if(argc<2)
    {
	printf("usage:hostname name|ip\n");	
	exit(1);
    }
    argv++;
    for(;*argv!=NULL;argv++)
    {
 	if(inet_aton(*argv,&addr.sin_addr)!=0)
	{
	    he=gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);
	    printf("address information of IP %s\n",*argv);
	}
	else{
	    he=gethostname(*argv);
	    printf("address information of host %s:\n",*argv);
	}
	if(he == NULL)
	{
	    printf("no address information of host\n");
	    continue;
	}
	printf("official name:%s\n",he->h_name);
	printf("name alias:\n");
	for(alias=he->h_aliases;*alias!=NULL;alias++)
 	{
	    printf("    %s\n",*alias);
	}
    }
}
