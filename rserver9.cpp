#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>

using namespace std;

void serverFunction();
int ssock, csock;  

int main() {
  unsigned int len;

  struct sockaddr_in server, client;  

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket: is not created");
    exit(-1);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);  
  server.sin_addr.s_addr = INADDR_ANY;  
  bzero(&server.sin_zero, 0);  

  len = sizeof(struct sockaddr_in);

  if ((bind(ssock, (struct sockaddr *)&server, len)) == -1) {  
    perror("find: ");
    exit(-1);
  }
  if ((listen(ssock, 5)) == -1) {  
    perror("listen: "); exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1) {  
    perror("accept: ");
    exit(-1);
  }

  while (1) {
		serverFunction(); 
    // DO STUFF HERE
  }
  close(ssock);
  return 0;
}
void serverFunction(){
	int n,c=0,m=0;
    char s[100];

    char ch;
	recv(csock, &n, sizeof(n), 0);
	recv(csock, s, sizeof(s), 0);
    map<char,int> mp;
    for(int i=0;s[i]!='\0';i++){
        mp[s[i]] += 1;
    }
    for(map<char, int> :: iterator it = mp.begin();it!=mp.end();++it){
        if(n== it->second){
            ch= it->first;
            break;
        }
        if(m< it->second){
            m= it->second;
            ch= it->first;
        }
    }
    send(csock, &ch, sizeof(ch), 0);
    printf("%c", ch);
}