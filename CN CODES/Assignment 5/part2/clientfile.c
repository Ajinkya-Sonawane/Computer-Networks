#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<stdlib.h>
#define PORT 7000

void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{
int sockfd, portno, n;
struct sockaddr_in serv_addr;

char buffer[256];

sockfd = socket(AF_INET, SOCK_STREAM, 0);

//if (sockfd,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

serv_addr.sin_port = htons(PORT);
serv_addr.sin_family=AF_INET;

if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
{
error("ERROR connecting");
}
bzero(buffer,256);
n = read(sockfd,buffer,255);
if (n < 0)
{
error("ERROR reading from socket");
}
printf("File contents: %s",buffer);
FILE *fpclient;
fpclient=fopen("clientfile.txt","w");
fputs(buffer,fpclient);
fclose(fpclient);
return 0;
}
