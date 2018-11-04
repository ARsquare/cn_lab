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

int check(int n){
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
	return x;
}

int main(){
	int sock;
	
	int n;
	int c;

	unsigned int len;
	struct sockaddr_in client;
	if( ( sock=socket(AF_INET,SOCK_STREAM,0))==-1 )
	{
		perror("error");
		exit(-1);
	}
	client.sin_family=AF_INET;
	client.sin_port=htons(10000);
	client.sin_addr.s_addr=INADDR_ANY;
	bzero(&client.sin_zero,0);

	len=sizeof(struct sockaddr_in);

	if( (connect( sock,( struct sockaddr *)&client , len) ) == -1 )
	{
		perror("error");
		exit(-1);
	}
	
	while(1)
	{
		
		cin>>n;
		n=n<<3;
		n^=check(n);
		send(sock,&n,sizeof(n),0);
		printf("\npress -1 to exit and 0 to continue\n");
		scanf("%d",&c);
		if(c==-1)
		{				
			close(sock);
			exit (0);
			break;
		}		
			
	}
	return 0;
}

