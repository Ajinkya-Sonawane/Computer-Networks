/*
	TCP p2p chat using C++ [CLIENT] 
		-Ajinkya Sonawane
	
	How to run the server :	|| g++ client.cpp && ./a.out IP_ADDRESS PORT_NO || (TODO: provide ip_address & port_no of your own choice) 	
	
	Example : g++ client.cpp && ./a.out 127.0.0.1 1234
		  
		  Here, IP_ADDRESS : 127.0.0.1
		  	PORT_NO	   : 1234
*/

#include<iostream>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>

using namespace std;

int main(int argc,char *argv[])
{

	int PROTOCOL = 0;	//TCP : 0	
	
	//TODO: declare socket file descriptor variable and port number variable
	int sockfd,portno;
	
	//TODO: declare socket structure object to hold server address 
	struct sockaddr_in serv_addr;
	
	//TODO: declare hostent structure pointer object to store the host name
	struct hostent *server;
	
	//TODO: convert port number accepted from command line to integer
	portno = atoi(argv[2]);
	
	//TODO: Create SOCKET() 
	sockfd = socket(AF_INET,SOCK_STREAM,PROTOCOL);
	
	if(sockfd < 0)
	{
		cerr<<"\nError in creating socket"<<endl;
		return 1;
	}
	
	//TODO: get the server by name(ip) given as command line argument
	server = gethostbyname(argv[1]);
	
	//if server is null then host was not found in the /etc/hosts file
	if(server == NULL)
	{
		cerr<<"\nNo such host found"<<endl;
		return 1;
	}
	
	//TODO: nullify the serv_addr object
	bzero((char *)&serv_addr,sizeof(serv_addr));
	
	//TODO: Initialize the socket object
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);	//Copies the host address from server object to serv_addr object
	serv_addr.sin_port = htons(portno);
	
	//TODO: Connect to the server 
	int conn_res = connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	//if connect() call returns value < 0 then error occurred while connecting
	if(conn_res < 0)
	{
		cerr<<"\nError in connecting to server"<<endl;
		return 1;
	}
	
	//TODO: declare buffer to accept and store messages
	char buffer[256];
	int n;
	
	//TODO: nullify the buffer to clear garbage value
	bzero(buffer,255);
		
	while(strcmp(buffer,"quit"))
	{
		//TODO: nullify the buffer to clear previously stored message
		bzero(buffer,255);
		
		//TODO: receive message from server into buffer
		n = recv(sockfd,&buffer,255,0);
		
		//if recv() call returns value < 0 then error occurred
		if(n < 0)
		{
			cout<<"\nError in reading message"<<endl;
			break;
		}
		cout<<"\nServer : "<<buffer;
		if(strcmp(buffer,"quit") == 0)
		{
			cout<<endl;
			break;
		}	
		//TODO: nullify the buffer 	
		bzero(buffer,255);
		
		cout<<"\nClient : ";
		cin.getline(buffer,255);
		
		//TODO: send the message stored in buffer to server
		send(sockfd,buffer,strlen(buffer),0);
	}
	
	return 0;
	
}
