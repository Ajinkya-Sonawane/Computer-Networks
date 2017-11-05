/*
	UDP File transer c++ [CLIENT/SENDER]
	- Ajinkya Sonawane
*/

#include<iostream>
#include<string.h>
#include<fstream>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
	//TODO: Internet Protocol : 0
	int PROTOCOL = 0;
	
	//TODO: declare struct sock_addr for server address	
	struct sockaddr_in serv_addr;
	
	//TODO: declare variables to store socket file descriptor and port number
	int sockfd,portno;
	
	if(argc < 2)
	{
		cout<<"\nMention IP and PORT number at runtime\n Example : ./a.out 127.0.0.1 1234\n";
		return 1;
	}
	
	
	//TODO: Create socket
	sockfd = socket(AF_INET,SOCK_DGRAM,PROTOCOL);
	if(sockfd < 0)
	{
		cout<<"\nError in creating\n";
		return 1;
	}
	
	//TODO: Initialize the socket
	bzero((char *)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	//TODO: declare variables for filename and path 
	char file_name[20],path[40];
	bzero(path,39);
	bzero(file_name,19);
	
	cout<<"Enter the path to the file : ";
	cin>>path;
	
	cout<<"\nEnter the filename to be sent : ";
	cin>>file_name;
	
	//TODO: Concat the path and file name
	strcat(path,"/");
	strcat(path,file_name);

	cout<<"\nGiven file : "<<path;
	
	//TODO: vairable to store the size of serv_addr structue
	unsigned int storage_size = sizeof(serv_addr);
	
	//TODO: Open the file to be sent
	fstream file;
	file.open(path,ios::in);
	
	//TODO: Send the file name to the server
	sendto(sockfd,file_name,strlen(file_name),0,(struct sockaddr *)&serv_addr,storage_size);
	
	//TODO: create buffer to read from file
	char buf[1024];
	bzero(buf,1024);
	
	//TODO: variables to check bytes sent,read and the total count
    	int count=0,bytes_sent,bytes_read;
    	
	//TODO: keep reading file till the end
	do
	{
		file.read(buf,1024);
       		bytes_read=file.gcount();

		cout<<"\r"<<"Sent : "<<count<<" bytes ";
		if(bytes_read==-1)
		{
			cout<<"Error in reading from file";
			return 1;
		}
		
		//TODO: send the read bytes to server
		bytes_sent=sendto(sockfd,buf,bytes_read,0,(struct sockaddr*)&serv_addr,storage_size);
		
		if(bytes_sent==-1)
		{
			cout<<"send error";
			return 1;
		}
		//TODO: Increment total count with the number of bytes sent
		count+=bytes_sent;
		
		//TODO: Clear the buffer
		bzero(buf,1024);
		
		//TODO: sleep for 100 miliseconds
		usleep(100);
		
	}while(bytes_read);
	
	//TODO: send 0 to server to terminate the loop in server end
	bytes_sent=sendto(sockfd,buf,0,0,(struct sockaddr*)&serv_addr,storage_size);
	
	cout<<"\nTotal bytes sent : "<<count<<endl;
	return 0;
}
