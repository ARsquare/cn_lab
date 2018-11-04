#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int fact(int n){
	if(n==0)
		return 1;
	return n*fact(n-1);
}

void main(){

	int ssock,csock;
	int n;
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
	n=fact(n);
	send(csock,&n,sizeof(n),0);           
	printf("Data sent =: %d\n",n);

	close(ssock);
}
