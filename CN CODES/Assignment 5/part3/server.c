/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

char arr[20];
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int compute(char num[],int len){
	int ans=0;
	int i=len-1;
	int mul=1;

	while(i>=0){
	int d=mul*(((int)num[i])-48);
	printf("\n %d",d);
	ans=ans+d;
	mul=mul*10;
	i--;
	}
	
	return ans;
}

int operate(int a,int b,char op){
switch(op){
	case'+':
	return a+b;
	break;
	case'-':
	return a-b;
	break;
	case'*':
	return a*b;
	break;
	case'/':
	return a/b;
	break;
	default:
	return 0;
}
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 portno=7000;
     //GET DESCRIPOR  (FAMILY TYPE PROTOCOL )
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     //portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     //BIND DESCRIPTOR SERVER_IP_PORT SIZE
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              
              error("ERROR on binding");
     //CANGE SOCKET UNCONNECTED TO PASSIVE (DESCRIPOR , NO OF CONNECTIONS(BACKLOG))
     //READY TO ACCEPT
     listen(sockfd,5);
     
     clilen = sizeof(cli_addr);
     
     // DESCRIPTOR ,CLIENT ADDR AND PORT, SIZEOF STRUCT 
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
                 
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     
    
     //
     int i=0;
     char num1[5];
     int l1=0;
     int l2=0;
     char num2[5];
     
     while(!(buffer[i]=='$'||buffer[i]=='+'||buffer[i]=='-'||buffer[i]=='*')){
   		 num1[l1]=buffer[i];
   	 	 l1++;
   		 i++;
     }
    
     char op=buffer[i];
     i++;
     while(!(buffer[i]=='$'||buffer[i]=='+'||buffer[i]=='-'||buffer[i]=='*')){
   		 num2[l2]=buffer[i];
   		 l2++;
   		 i++;
     }
     	
     
     int a=compute(num1,l1);
     int b=compute(num2,l2);
     printf("\n NUM 1=%d",a);
     printf("\n Num 2=%d",b);
     
     int c=operate(a,b,op);
     char ans[255];
     printf("\n Ans op int= %d",c);
     int d=c;
     int place=0;
     
    /* while(d>0){
     ans[place]=(char)((d%10)+48);
     d=d/10;
     place++;
     }
     //
     */
     sprintf(ans,"%d",c);
     printf("\n Ans char arr= %s",ans);
     //int number_to_send = 35;
	//int converted_number = htonl(number_to_send);
	


     printf("\n Here is the Question: %s\n",buffer);
     printf("\n ANSWER=%d",c);
     //n = write(newsockfd,"I got your Question",18);
     n = write(newsockfd,ans,255);
     
     //write(newsockfd, &converted_number, sizeof(converted_number));
     //write(newsockfd, &number_to_send,sizeof(number_to_send));
    // n = write(newsockfd,"Answer Found!%d",ans,18);
     //n = write(newsockfd,ans,5);
    // n=write(newsockfd,&c,sizeof(c));
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
