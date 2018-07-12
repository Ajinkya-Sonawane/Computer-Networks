
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
exit(1);
}

int main(int argc, char *argv[])
{

int sockfd, newsockfd;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
int clilen=sizeof(cli_addr);

sockfd = socket(AF_INET, SOCK_STREAM, 0);

if (sockfd < 0)
{
error("ERROR opening socket");
}


serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port =htons(PORT);

if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
{
error("ERROR on binding");
}

listen(sockfd,3);


newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,(socklen_t*)&clilen);

if (newsockfd < 0)
{
error("ERROR on accept");
}

bzero(buffer,256);

FILE *fp;
fp=fopen("serverfile.txt", "r");
fgets(buffer,200,fp);

/*n = read(newsockfd,buffer,255);

if (n < 0)
{
error("ERROR reading from socket");
}*/

printf("Sending contents to client\n");

n = send(newsockfd,buffer,256,0);
if (n < 0)
{
error("ERROR writing to socket");
}

fclose(fp);
return 0;
}
