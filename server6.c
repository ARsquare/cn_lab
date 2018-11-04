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
  char s[1000];
  int n,i,j,k,c=0;
  struct sockaddr_in server,client;

  unsigned int len=sizeof(struct sockaddr_in);

  if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("Cannot create server\n");
    exit(-1);
  }

  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(10000);
  bzero(&server.sin_zero,0);

  if(bind(ssock,(struct sockaddr*)&server,len)==-1){
    perror("Cannot bind\n");
    exit(-1);
  }

  if(listen(ssock,5)==-1){
    perror("Cannot listen\n");
    exit(-1);
  }

  if((csock=accept(ssock,(struct sockaddr*)&client,&len))==-1){
    perror("Cannot accept\n");
    exit(-1);
  }

  recv(csock,&n,sizeof(n),0);
  printf("Data received\n");
  for(i=0;i<n;i++){
    for(j=0;j<i;j++)
      s[c++]=' ';
    for(;j<n;j++)
      s[c++]='*';
    s[c++]='\n';
  }  
  printf("Data sent\n");

  send(csock,&s,sizeof(s),0);

  close(ssock);

}
