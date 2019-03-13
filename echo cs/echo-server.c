#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
typedef struct sockaddr SA;
void echo(int connfd);
int main(int argc,char **argv){
	int listenfd,connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	char client_hostname[1024],client_port[1024];
	if(argc!=2){
		fprintf(stderr,"usage:%s<port>\n",argv[0]);
		exit(0);
	}

	listenfd=open_listenfd(argv[1]);
	while(1){
		clientlen=sizeof(struct sockaddr_storage);
		connfd=accept(listenfd,(SA*)&clientaddr,&clientlen);
		getnameinfo((SA*)&clientaddr,clientlen,client_hostname,1024,client_port,1024,0);
		printf("connected to (%s %s)\n",client_hostname,client_port);
		echo(connfd);
		close(connfd);
	}
	exit(0);
}

void echo(int connfd){
	size_t n;
	char buf[1024];
	//n=read(STDIN_FILENO,buf,1024);
	//write(connfd,buf,n);
	while((n=read(connfd,buf,1024))!=0){
		printf("server received %d bytes\n",(int)n);
		write(STDOUT_FILENO,buf,n);
		write(connfd,buf,n);
	}
}
