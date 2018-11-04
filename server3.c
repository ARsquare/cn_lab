#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

char grade(int n){
	if(n>=85 && n<=100)
		return 'A';
	if(n>=70 && n<85)
		return 'B';
	if(n>=60 && n<69)
		return 'C';
	if(n>=50 && n<59)
		return 'D';
	else
		return 'F';
}
void main(){

	int ssock,csock;
	int n;
	char g;
	unsigned int len;

	struct sockaddr_in server,client;

	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: is not created");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(10000);
	server.sin_addr.s_addr=INADDR_ANY;

	bzero(&server.sin_zero,0);


	len=sizeof(struct sockaddr_in);

	if((bind(ssock,(struct sockaddr *)&server,len))==-1){
		perror("bind: ");
		exit(-1);
	}


	if((listen(ssock,5))==-1){
		perror("listen: ");
		exit(-1);
	}


	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){
		perror("accept: ");
		exit(-1);
	}


	recv(csock,&n,sizeof(n),0);
	g=grade(n);
	send(csock,&g,sizeof(g),0);
	printf("Data sent =: %c\n",g);

	close(ssock);
}
