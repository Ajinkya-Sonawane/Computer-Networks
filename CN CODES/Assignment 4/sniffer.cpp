/*
	Program to capture packets on the network [C++]	
	- Ajinkya Sonawane
*/

#include<iostream>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fstream>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/if_ether.h>
#include<netinet/ip.h>
#include<unistd.h>

using namespace std;

void ProcessPacket(unsigned char*,int);
void print_ether_header(unsigned char *,int);
void print_ip_header(unsigned char *,int);
void print_tcp_packet(char*,int);
void print_udp_packet(char*,int);
void print_icmp_packet(char*,int);

char* convert(unsigned char* addr)
{
	static char str[18];
	bzero(str,18);
	if(addr == NULL) return str;

	snprintf(str, sizeof(str), "%02x:%02x:%02x:%02x:%02x:%02x", 
	     addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	return str;
}

//TODO: GLOBAL VARIRABLES
struct sockaddr_in source,dest;
int tcp=0,udp=0,icmp=0,igmp=0,others=0,total=0;

//TODO: create logfile
fstream logfile;


int main()
{
	//TODO: create sockaddr structure to store server address
	struct sockaddr serv_addr;
	
	//TODO: declare variables to store the size of server address and received data
	unsigned int serv_addr_len;
	int bytes_recv;
	
	//TODO: socket descriptor 
	int sockfd;
	
	//TODO: create a buffer
	unsigned char buffer[65536];
	
	logfile.open("log.txt",ios::out);
	if(!logfile.is_open())
	{
		cout<<endl<<"Error in creating log file";
		return 1;
	}
	
	cout<<"\nStarting.....\n";
	
	int PROTOCOL = htons(ETH_P_ALL);
	
	//TODO: create raw socket 
	sockfd = socket(AF_PACKET,SOCK_RAW,PROTOCOL);
	
	if(sockfd < 0)
	{
		cout<<"\nError in creating socket\n";
		return 1;
	}
	
	serv_addr_len = sizeof(serv_addr);
	
	while(true)
	{
		bytes_recv = recvfrom(sockfd,&buffer,65535,0,&serv_addr,&serv_addr_len);
		if(bytes_recv < 0)
		{
			cout<<"\nError in recieving packets\n";
			return 1;
		}
		//TODO; process the packet
		ProcessPacket(buffer,bytes_recv);
	}
	close(sockfd);
	logfile.close();
	cout<<"\nFinished...\n";
	return 0;
}

void ProcessPacket(unsigned char *buffer,int size)
{
	struct iphdr *ip = (struct iphdr*)(buffer+sizeof(struct ethhdr));
	++total;
	//print_ether_header(buffer,size);
	print_ip_header(buffer,size);
	switch(ip->protocol)
	{
		case 1:
			++icmp;
			break;
		case 2:
			++igmp;
			break;
		case 6:
			++tcp;
			break;
		case 17:
			++udp;
			break;
		default:
			++others;
			break;
	}	
	cout<<"\rTCP : "<<tcp<<" UDP : "<<udp<<" ICMP : "<<icmp<<" IGMP : "<<igmp<<" Others : "<<others<<" Total : "<<total;
}

void print_ether_header(unsigned char *buffer,int size)
{
	struct ethhdr *eth = (struct ethhdr *)&buffer;
	logfile<<"\n";
	logfile<<"Ethernet Header \n";
	logfile<<"    |-Destination Address : "<<convert(eth->h_dest)<<endl;
	
	logfile<<"    |-Source Address      : "<<convert(eth->h_source)<<endl;		
	
	logfile<<"    |-Protocol            : "<<eth->h_proto<<endl;            		
}

void print_ip_header(unsigned char *buffer,int size)
{	
	print_ether_header(buffer,size);
	
	unsigned int ip_header_len;
	struct iphdr *ip = (struct iphdr*)(buffer+sizeof(struct ethhdr));
	ip_header_len == ip->ihl*4;
	
	bzero((char *)&source,sizeof(source));
	bzero((char *)&dest,sizeof(dest));
	
	source.sin_addr.s_addr = ip->saddr;
	dest.sin_addr.s_addr = ip->daddr;
	
	logfile << "\n";
	logfile << "IP HEADER\n";
	logfile << "	|-IP Version		: "<<(unsigned int)ip->version<<endl;
	logfile << "	|-IP Header Length 	: "<<(unsigned short)ip->ihl<<" DWORDS "<<(unsigned int)ip_header_len<<" BYTES \n";
	logfile << "	|-Type of Service	: "<<(unsigned int)ip->tos<<endl;
	logfile	<< "	|-IP Total Length	: "<<ntohs(ip->tot_len)<<endl;
	logfile << "	|-Identification	: "<<ntohs(ip->id)<<endl;
	logfile << "	|-TTL			: "<<(unsigned int)ip->ttl<<endl;
	logfile << "	|-Protocol		: "<<(unsigned int)ip->protocol<<endl;
	logfile << "	|-Checksum		: "<<ntohs(ip->check)<<endl;
	logfile << "	|-Source IP		: "<<inet_ntoa(source.sin_addr)<<endl;
	logfile << "	|-Destination IP	: "<<inet_ntoa(dest.sin_addr)<<endl;
}



