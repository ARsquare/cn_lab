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

struct stud
{
    char name;
    int roll ;
    int age;
    char single;
    float income;
};

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
  int a;
  struct stud c; 

    printf("enter student roll no:\n");
    scanf("%d",&a);
    send(sock,&a,sizeof(a),0);
    recv(sock,&c,sizeof(c),0);

    printf("\nstudents info=:\n name = %c, roll = %d, age = %d, single = %c, income = %f",c.name,c.roll,c.age,c.single,c.income);


}
