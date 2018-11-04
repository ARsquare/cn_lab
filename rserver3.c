#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

void serverFunction();
int ssock, csock;  

void main() {
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
}
void serverFunction(){
	int a; 
	recv(csock, &a, sizeof(a), 0);
	char gr;
    if(85<=a && a<=100)
        gr='A';
    else if(70<=a && a<=84)
        gr='B';
    else if(60<=a && a<=69)
        gr='C';
    else if(50<=a && a<=59)
        gr='D';
    else if(0<=a && a<=50)
        gr='E';
    printf("%d", gr);
	send(csock, &gr, sizeof(gr), 0);
}