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

struct stud{
    char name;
    int roll ;
    int age;
    char single;
    float income;
};

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
      struct stud students[10];
    for(int i=0;i<10;i++)
    {
        students[i].name = 'a'+i;
        students[i].roll = i+10;
        students[i].age = i+20;
        students[i].single = (i%2)?'y':'n';
        students[i].income = ((i%2)*100+i%3*10+i);
    }

    struct stud c;
	recv(csock, &n, sizeof(n), 0);
	if(n<=10)
    { 
        c = students[n];
        send(csock,&c,sizeof(c),0);

        printf("\nstudents info=:\n name = %c, roll = %d, age = %d, single = %c, income = %f",students[n].name,students[n].roll,students[n].age,students[n].single,students[n].income);
    }
    else
        printf("student not exists\n");
}