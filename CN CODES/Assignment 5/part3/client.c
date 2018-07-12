#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	
     printf( argv[0],"\n");
     printf( argv[1],"\n");
     printf( argv[2],"\n");
   
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
   
     //CONVERT PORT TO INT
    portno = atoi(argv[2]);
    
    //SET FILE DESCRPTOR ON FAMILY TYPE PROTOCOL
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    
    if (sockfd < 0) 
        error("ERROR opening socket");
        
    //STORE NAME/IP INTO HOSTNET SERVER    
    server = gethostbyname(argv[1]);
    
    
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    //FAMILY SET !!!!
    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
         
         
     // PORT NUMBER SET !!!!!
    serv_addr.sin_port = htons(portno);
    
    
    //CONNECT DESCTIPOR TO ,PORT AND ADDR OF REQ SERVER,SIZE OF SERVER  
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
   // int rev;
    //int *ptr;
    //ptr=&rev;

    n = read(sockfd,buffer,255);
    //n = read(sockfd,ptr,4);
    
    int tmp,num;
	//read(sockfd, &tmp, sizeof(tmp));
	//num = ntohl(tmp);
   // printf("%d \n",tmp);
   n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
         printf("Anwser from the server \n");
         
         printf("%s \n",buffer);
         
    //int num =ntohl(*ptr);

  
    
    // CLOSE DESCRIPOR
    close(sockfd);
    return 0;
}
