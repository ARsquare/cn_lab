#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
struct wo
{
char ques[100];
char ans[100];
};
void main(){int sock;
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
equal in size with 'struct sockaddr'..
len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){ //conneting to client
perror("connect: ");
exit(-1);
}
char a[100];
struct wo b;int y;int c=0;
while(i!=-1&&c<3){scanf("%s",a);
send(sock,&a,sizeof(a),0);
recv(sock,&b,sizeof(b),0);
//recv(sock,&c,sizeof(c),0);
printf("The answer is %s \n",b.ans);
printf("Press 1 to exit and 0 to continue\n");
scanf("%d",&y);
if(y==0)
i=1;
else
i=-1;
c++;
}
// receiving data from client
//printf("\ndo you want to exit...press 'no'\n");
//scanf("%s",ch1);
//printf("%s\n",ch1);
//printf("%s\n",ch);
close(sock);
exit(0);
}