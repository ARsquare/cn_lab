#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
	int ssock,csock;
	struct sockaddr_in server,client;
	unsigned int len;
	char s[100];
	char m[100]="Hello and welcome!";
	char p[6]="qwerty";

	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Socket not created\n");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(10000);
	server.sin_addr.s_addr=INADDR_ANY;

	bzero(&server.sin_zero,0);

	len=sizeof(struct sockaddr_in);

	if(bind(ssock,(struct sockaddr*)&server,len)==-1){
		perror("Cannot bind\n");
		exit(-1);
	}


	if(listen(ssock,5)==-1){
		perror("Cannot listen\n");
		exit(-1);
	}

	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){
		perror("Cannot accept");
		exit(-1);
	}

	recv(csock,&s,sizeof(s),0);
	if(strcmp(s,p)==0){
		send(csock,&m,sizeof(m),0);
	}
	close(ssock);

}
