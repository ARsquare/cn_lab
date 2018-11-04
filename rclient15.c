#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
int main(int argc, char * argv[])
{
int sockfd = 0;
char sendBuff[1025];
struct sockaddr_in serv_addr;
/* Create a socket first */
if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
{
printf("\n Error : Could not create socket \n");
return 1;
}
/* Initialize sockaddr_in data structure */
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000); // port
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
/* Attempt a connection */
if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
{
printf("\n Error : Connect Failed \n");
return 1;
}
if(argc!=2)
{
printf("incorrect usage\n");
return 0;
}
char file_name[20];
strcpy(file_name,argv[1]);
send(sockfd,&file_name,sizeof(file_name),0);
/* Create file where data will be stored */
FILE *fp;
fp = fopen(file_name, "rb");
if(NULL == fp)
{
printf("Error opening file");
return 1;
}
/* Read data from file and send it */
while(1){
/* First read file in chunks of 256 bytes */
unsigned char buff[256]={0};
int nread = fread(buff,1,256,fp);
printf("Bytes read %d \n", nread);
/* If read was success, send data. */
if(nread > 0)
{
printf("Sending \n");
write(sockfd, buff, nread);
}
if (nread < 256)
{
if (feof(fp))
printf("End of file\n");
if (ferror(fp))
printf("Error reading\n");
break;
}
}
return 0;
}