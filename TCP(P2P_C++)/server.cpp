/*
	TCP p2p chat using C++ [SERVER] 
		-Ajinkya Sonawane

	How to run the server :	g++ server.cpp && ./a.out PORT_NO (TODO: provide port_no of your own choice) 	
	
	Example : g++ server.cpp && ./a.out 1234
		
		Here, PORT_NO	   : 1234
*/

#include<iostream>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>

using namespace std;

int main(int argc,char *argv[])
{
	//TCP PROTOCOL : 0
	int PROTOCOL = 0;
	
	//TODO: declare socket descriptors ,port variable
	int sockfd,newsockfd,portno;
	
	//TODO: declare variable to store length of the client address
	unsigned int clilen;

	//TODO: create object of sockaddr_in to store server and client address
	struct sockaddr_in serv_addr,cli_addr;
	
	//TODO: Call the SOCKET() function which will return the socket file descriptor as an integer value
	sockfd = socket(AF_INET,SOCK_STREAM,PROTOCOL);
	
	/*
		AF_INT		: Socket address family for INTERNET
		SOCK_STREAM	: Socket type   
	*/
	
	//if sockfd is less than 0 then socket is not created
	if(sockfd < 0)
	{
		cerr<<"Error opening socket";
		return 1;	//EXIT
	}
	
	//TODO: Initialize the SOCKET structure for server
	bzero((char *)&serv_addr,sizeof(serv_addr));
	
	//TODO: Assign the port number
	portno = 12345;
	
	//TODO: provide the values for the socket structure
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	//TODO: Now bind the host address using BIND() call
	int bind_res = bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	//if the bind() call returns value < 0 then binding failed
	if(bind_res < 0)
	{
		cerr<<"Error on binding";
		return 1;
	}
	
	//TODO: Now start listening for the clients
	listen(sockfd,5);
	
	//store the address of client address structure in a variable
	clilen = sizeof(cli_addr);
	
	
	//TODO: Accept the connection from the client
	newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	
	//if accept() call return value < 0 then error on accepting connection
	if(newsockfd < 0)
	{
		cerr<<"Error on accepting";
		return 1;
	}
	
	//TODO: if client is connected then start communicating
		
	//TODO: create a buffer to accept and store messages
	char buffer[256];
	int n;
	
	//TODO: nullify the buffer to clear garbage value
	bzero(buffer,255);
		
	
	while(strcmp(buffer,"quit"))
	{
		//TODO: nullify the buffer 
		bzero(buffer,255);
		
		cout<<"\nSERVER : ";
		cin.getline(buffer,255);
		
		//TODO: send message to client
		send(newsockfd,buffer,strlen(buffer),0);
		
		if(strcmp(buffer,"quit") == 0)
		{	
			cout<<endl;
			break;
		}
		//TODO: nullify buffer to clear previously stored message
		bzero(buffer,255);
		
		//TODO: receive incoming message
		n = recv(newsockfd,&buffer,255,0);
		
		//if recv() call returns value < 0 then error occurred
		if(n < 0)
		{
			cerr<<"\nError in reading message"<<endl;
			break;
		}
		
		cout<<"\nClient : "<<buffer<<endl;	
	}
	
	return 0;
}
