#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

void clientFunction();
int sock;
void main() {
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
}

void clientFunction(){
  int m,n; 
  printf("Enter the numbers: ");
  scanf("%d %d", &m, &n);
  send(sock, &m, sizeof(m), 0);
  send(sock, &n, sizeof(n), 0);
  int a,b,c,d; 
  recv(sock, &a, sizeof(a), 0);
  recv(sock, &b, sizeof(b), 0);
  recv(sock, &c, sizeof(c), 0);
  recv(sock, &d, sizeof(d), 0);
  printf("The results are : %d, %d, %d, %d\n",a, b, c, d);
}
