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
	int n; 
	recv(csock, &n, sizeof(n), 0);
	int k=0,p[n];
    for(int i=2;i<n/2;i++){
        if(n%i==0){
            int flag=0;
            for(int j=2;j<i/2;j++)
                if(i%j==0)
                    flag=1;
            if(flag==0)
                p[k++]=i;

        }
    } 
	send(csock, &k, sizeof(k), 0);
	send(csock, &p, sizeof(p), 0);
    printf("%d", k);
}