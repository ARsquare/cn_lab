#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string.h>

void main(){
	int sock;
	unsigned int len;
	int n;
	int a,b;
  int s,p,d,q;

	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}

	client.sin_family=AF_INET;
	client.sin_port=htons(10000);
	client.sin_addr.s_addr=INADDR_ANY;

	bzero(&client.sin_zero,0);


	len=sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr *)&client,len))==-1){
		perror("connect: ");
		exit(-1);
	}

	printf("Enter 2 no\n");
	scanf("%d",&a);
  scanf("%d",&b);

	send(sock,&a,sizeof(a),0);
  send(sock,&b,sizeof(b),0);


	recv(sock,&s,sizeof(s),0);
  recv(sock,&d,sizeof(d),0);
  recv(sock,&p,sizeof(p),0);
  recv(sock,&q,sizeof(q),0);

	printf("Sum = %d\n",s);
  printf("Difference = %d\n",d);
  printf("Product = %d\n",p);
  printf("Quotient = %d\n",q);
  
	close(sock);
}
