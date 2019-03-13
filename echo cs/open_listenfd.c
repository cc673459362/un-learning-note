#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
typedef struct sockaddr SA;
int open_listenfd(char *port){
	struct addrinfo hints,*listp,*p;
	int listenfd,optval=1;

	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
	hints.ai_flags|=AI_NUMERICSERV;
	getaddrinfo(NULL,port,&hints,&listp);

	for(p=listp;p;p=p->ai_next){
		if((listenfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)	continue;     //socket failed, try the next;
		setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&optval,sizeof(int));
		if(bind(listenfd,p->ai_addr,p->ai_addrlen)==0)
			break;
		close(listenfd);
	}

	freeaddrinfo(listp);
	if(!p)
		return -1;

	if(listen(listenfd,1024)<0){
		close(listenfd);
		return -1;
	}
	return listenfd;
}
