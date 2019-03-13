#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
typedef struct sockaddr SA;

int main(int argc,char** argv){
	int clientfd;
	char *host,*port,buf[1024];
	if(argc!=3){
		fprintf(stderr,"usagee:%s<host><port>\n",argv[0]);
		exit(0);
}
	host=argv[1];
	port=argv[2];
	clientfd=open_clientfd(host,port);
	size_t n;
	while((n=read(STDIN_FILENO,buf,1024))!=0){
		write(clientfd,buf,n);
		n=read(clientfd,buf,1024);
		write(STDOUT_FILENO,buf,n);
	} 
	close(clientfd);
	exit(0);
}



