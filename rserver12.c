#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>
struct wo
{
char ques[100];
char ans[100];
};
int size=0;
void main(){
int ssock,csock;
// creating server and clinet socket discriptor
int n;
int i,j;
unsigned int len;
struct sockaddr_in server,client; // creating server & client socket object
if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
perror("socket: is not created");
exit(-1);
}
server.sin_family=AF_INET;server.sin_port=htons(10001);
// initializing server socket parameters..
server.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'..
len=sizeof(struct sockaddr_in);
if((bind(ssock,(struct sockaddr *)&server,len))==-1){ // binding port & IP
perror("bind: ");
exit(-1);
}
if((listen(ssock,5))==-1){
// listening for client
perror("listen: ");
exit(-1);
}
if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){ // accepting connectn
perror("accept: ");
exit(-1);
}
struct wo w[20];
strcpy(w[0].ques,"name");
strcpy(w[0].ans,"ashwini");
strcpy(w[1].ques,"place");
strcpy(w[1].ans,"dhanbad");
strcpy(w[2].ques,"home");strcpy(w[2].ans,"patna");
strcpy(w[3].ques,"branch");
strcpy(w[3].ans,"cse");
strcpy(w[4].ques,"rank");
strcpy(w[4].ans,"3375");
/*
w[5].word="asd";
w[5].meaning="sdf";
w[6].word="dfg";
w[6].meaning="fgh";
w[7].word="ghj";
w[7].meaning="hjk";
w[8].word="jkl";
w[8].meaning="zxc";
w[9].word="xcv";
w[9].meaning="cvb";*/
char a[100];
size=5;int flag=0;int c=0;
while(1){
recv(csock,&a,sizeof(a),0);
for(i=0;i<size;i++)
{
if(strcmp(a,w[i].ques)!=0)
continue;
else
{
send(csock,&w[i],sizeof(w[i]),0);
printf("Answer is %s\n",w[i].ans);
}}
/*if(flag==0)
{
strcpy(w[size].word,a);
c=1;
size++;
}
send(csock,&c,sizeof(c),0);*/
}
close(ssock);
}