/*
	UDP File transer c++ [SERVER/RECIEVER]
	- Ajinkya Sonawane
*/

#include<iostream>
#include<string.h>
#include<netdb.h>
#include<fstream>
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
	
	if(argc < 3)
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
	
	//TODO: Bind the socket 
	int bind_res = bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(bind_res < 0)
	{
		cout<<"\nError in binding\n";
		return 1;
	}
	
	cout<<"\nSERVER READY TO RECEIVE.....\n";
	
	//TODO: vairable to for sockaadr structue
	struct sockaddr_storage serv_storage;
	unsigned int storage_size = sizeof(serv_storage);
	
	//TODO: declare variables to check number of bytes received
	int bytes_recv;
	
	//TODO: Buffer to store received bytes and variable to store file name
	char buf[1024];
	char file_name[30];
	bzero(file_name,29);
	
	//TODO: Accept the file name from the sender
	int check = recvfrom(sockfd,&file_name,29,0,(struct sockaddr *)&serv_addr,&storage_size);
	if(check < 0)
	{
		cout<<"\nError in receiving file name \n";
		return 1;
	}

	//TODO: Open the file to write
	fstream file;
	file.open(file_name,ios::out);
	cout<<endl;
	
	//TODO: declare variables to store count of bytes written to file and total bytes received
	
	int count=0,bytes_wr;
	
	do
	{
		//TODO: Accept bytes in buffer
		bytes_recv=recvfrom(sockfd,&buf,1024,0,(struct sockaddr *)&serv_addr,&storage_size);
		if(bytes_recv==-1){
			cout<<"read fails";
			return EXIT_FAILURE;
		}
		
		//TODO: Increment the total count with the number of bytes received
		count+=bytes_recv;
		
		//TODO: Write the received bytes to file
		file.write(buf,bytes_recv);
		
		//TODO: Cleare the buffer
		bzero(buf,1024);
     		cout<<"\rFetching : "<<count;
	}while(bytes_recv);	

	cout<<"\nTotal bytes fetched : "<<count<<endl;
	
	return 0;
}
