#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

bool check(int n){
	int d=11;
	int x=n;
	x=x>>3;
	int t;
		//cout<<x<<" ";
	for(int i=2;i>=0;i--){
		if((x>>3&1)==0){
			x=x<<1;
			x|=(n&(1<<i));
			//cout<<x<<" ";
			continue;
		}
		t=x^d;
		t=t<<1;
		t|=(n&(1<<i));
		x=t;
			//cout<<x<<" ";
	}
	x=x^d;
	if(x)return 0;
	else return 1;
}


int main()
{
	int ssock,csock;
	
	int n;
	
	
	unsigned int len;
	struct sockaddr_in server,client;
	if( ( ssock=socket(AF_INET,SOCK_STREAM,0))==-1 ) 
	{
		perror("error");
		exit(-1);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(10000);
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,0);
	
	len=sizeof(struct sockaddr_in);
	
	if((bind(ssock,(struct sockaddr *)&server,len) )==-1)
	{
		perror("error bind");
		exit(-1);
	}
	if((listen(ssock,5))==-1){
		perror("error listen");
		exit(-1);
	}
	if((csock=accept(ssock,(struct sockaddr *)&client,&len) )==-1)
	{
		perror("error accept");
		exit(-1);
	}
	
	
	
	while(1)
	{
	
		recv(csock,&n,sizeof(n),0);
		if( check(n) ) cout<<"correctly recieved"<<endl;
		else cout<<"error found"<<endl;
		
	}
	close(ssock);
	return 0;
	
}

