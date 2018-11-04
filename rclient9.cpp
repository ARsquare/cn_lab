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


void clientFunction();
int sock;
int main() {
  int i;
  unsigned int len;

  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
  // client socket is created..
    perror("socket: ");
    exit(-1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10000);  
  // initializing  socket  parameters
  client.sin_addr.s_addr = INADDR_ANY;  
  // inet_addr("127.0.0.1");
  bzero(&client.sin_zero, 0);  
  // appending 8 byte zeroes to 'struct sockaddr_in', to make it
  // equal in size with 'struct sockaddr'..

  len = sizeof(struct sockaddr_in);
  if ((connect(sock, (struct sockaddr *)&client, len)) == -1) {  
  // conneting to client
    perror("connect: ");
    exit(-1);
  }
  while (1) {
    clientFunction();  
    // CHANGED THIS FUNCTION FOR QUESTIONS
    printf("do you want to continue...press 'y' or 'n'\n");
    char ip; scanf(" %c", &ip);
    if(ip=='n') {
      close(sock); exit(0);
    }
  }
  return 0;
}

void clientFunction(){
  int n,i;
  string s;
  cin >> n >> s;
  char c[100];
  for(i=0;i<s.length();i++){
      c[i]=s[i];
  }
  c[i]='\0';
  send(sock, &n, sizeof(n), 0);
  send(sock, c, sizeof(c), 0);
  char ch;
  recv(sock, &ch, sizeof(ch), 0);
  printf("The result is: %c\n",ch);
}
