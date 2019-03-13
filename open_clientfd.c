#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
typedef struct sockaddr SA;

int open_clientfd(char *hostname,char *port){
	struct addrinfo hints,*listp,*p;
	int clientfd;

	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_ADDRCONFIG;
	hints.ai_flags|=AI_NUMERICSERV;
	getaddrinfo(hostname,port,&hints,&listp);

	for(p=listp;p;p=p->ai_next){
		if((clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)	continue;     //socket failed, try the next;
		
		if(connect(clientfd,p->ai_addr,p->ai_addrlen)!=-1)
			break;
		close(clientfd);
	}

	freeaddrinfo(listp);
	if(!p)
		return -1;

	else
		return clientfd;
}
