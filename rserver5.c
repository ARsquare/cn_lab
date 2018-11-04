#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

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
	int n; 
	recv(csock, &n, sizeof(n), 0);
    char p[100];int k=0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++)
            p[k++]='*';
        p[k++]='\n';
    }
    p[k]='\0';
    int i=0;
    while(p[i++]!='\0')
        printf("%c", p[i]);
	send(csock, &p, sizeof(p), 0);
}