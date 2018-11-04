#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
int main(void)
{
int listenfd = 0;
int connfd = 0;
struct sockaddr_in serv_addr;
char sendBuff[1025];
int numrv;
int bytesReceived = 0;
char recvBuff[256];
memset(recvBuff, '0', sizeof(recvBuff));
listenfd = socket(AF_INET, SOCK_STREAM, 0);
printf("Socket retrieve success\n");memset(&serv_addr, '0', sizeof(serv_addr));
memset(sendBuff, '0', sizeof(sendBuff));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(5000);
bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(listen(listenfd, 10) == -1)
{
printf("Failed to listen\n");
return -1;
}
while(1)
{
connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
char file_name[20];
recv(connfd,&file_name,sizeof(file_name),0);
printf("file name : %s\n",file_name);
/* Open the file that we wish to transfer */
FILE *fp = fopen(file_name,"ab");
if(fp==NULL)
{
printf("File opern error");
return 1;
}
/* Receive data in chunks of 256 bytes */
while((bytesReceived = read(connfd, recvBuff, 256)) > 0)
{
printf("Bytes received %d\n",bytesReceived);
// recvBuff[n] = 0;
fwrite(recvBuff, 1,bytesReceived,fp);
// printf("%s \n", recvBuff);
}
if(bytesReceived < 0)
{
printf("\n Read Error \n");
}
fflush(fp);
close(connfd);
sleep(1);
break;
}
return 0;}