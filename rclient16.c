#include <stdio.h>
#include <stdlib.h>#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
void main(){
int sock;
// client socket discriptor
int n;int i;
int j;
i=0;
unsigned int len;
//char ch[3]="no";
//char ch1[3];
struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){ // client socket is created..
perror("socket: ");
exit(-1);
}
client.sin_family=AF_INET;
client.sin_port=htons(10001);
// initializing socket parameters
client.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it
equal in size with 'struct sockaddr'..len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){ //conneting to client
perror("connect: ");
exit(-1);
}
char b[100];char d[100];char e[100];
//struct wo b;int y;
int c;
while(i!=-1){
scanf("%s",b);
send(sock,&b,sizeof(b),0);
//recv(sock,&b,sizeof(b),0);
recv(sock,&c,sizeof(c),0);
recv(sock,&d,sizeof(d),0);
if(c==1)
{
printf("%s\n",d);
printf("Try again\n");
i=0;
}
else if(c==0)
{
printf("Say something to server\n");
scanf("%s",e);
printf("Server replies with %s\n",d);
i=-1;
}}
// receiving data from client
//printf("\ndo you want to exit...press 'no'\n");
//scanf("%s",ch1);
//printf("%s\n",ch1);
//printf("%s\n",ch);
close(sock);
exit(0);
}