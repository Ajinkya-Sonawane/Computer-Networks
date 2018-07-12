#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sockfd,newsockfd,bfd;
	char buf[256];
	struct sockaddr_in servadd;
	int n;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("ERROR opening socket");
		exit(1);
	}
	bzero((char*)&servadd,sizeof(servadd));
	servadd.sin_family=AF_INET;
	servadd.sin_addr.s_addr=INADDR_ANY;
	servadd.sin_port=htons(7000);
	bfd=bind(sockfd,(struct sockaddr*)&servadd,sizeof(servadd));
	if(bfd<0){
		perror("ERROR on binding");
		exit(1);
	}
	listen(sockfd,5);
	newsockfd=accept(sockfd,0,0);
	
	if(newsockfd<0)
	{
		perror("ERROR on accept");
		exit(1);
	}
	bzero(buf,256);
	n=read(newsockfd,buf,255);
	if(n<0)
	{
		perror("ERROR on reading from socket");
		exit(1);
	}
	printf("Client's message: %s",buf);
	n=write(newsockfd,"Hello client!",13);
	if(n<0)
	{
		perror("ERROR writine to socket");
		exit(1);
	}
	return 0;
}
