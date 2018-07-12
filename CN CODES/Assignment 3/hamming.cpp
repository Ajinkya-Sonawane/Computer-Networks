#include <iostream>
using namespace std;
void receive(bool datarec[11])
{
	bool rec[4];
	rec[0]=datarec[0]^datarec[2]^datarec[4]^datarec[6]^datarec[8]^datarec[10];
	rec[1]=datarec[1]^datarec[2]^datarec[5]^datarec[6]^datarec[9]^datarec[10];
	rec[3]=datarec[3]^datarec[4]^datarec[5]^datarec[6];
	rec[7]=datarec[7]^datarec[8]^datarec[9]^datarec[10];
	cout<<"Error found at position:  ";
	cout<<rec[7];
	cout<<rec[3];
	cout<<rec[1];
	cout<<rec[0];
}
void transmit(bool dat[7])
{
	bool datared[11];
	int i;
	for(i=6;i>=4;i--)
		datared[i+4]=dat[i];
	for(i=3;i>=1;i--)
		datared[i+3]=dat[i];
	datared[2]=dat[0];
	
	
	datared[0]=datared[2]^datared[4]^datared[6]^datared[8]^datared[10];
	datared[1]=datared[2]^datared[5]^datared[6]^datared[9]^datared[10];
	datared[3]=datared[4]^datared[5]^datared[6];
	datared[7]=datared[8]^datared[9]^datared[10];
	
	cout<<"Data with redundancy="<<endl;
	for(i=10;i>=0;i--)
		cout<<datared[i];
	cout<<endl;
	datared[10]=!datared[10];
	receive(datared);
}
int main()
{
	bool dat[7];
	int i;
	cout<<"Enter 7 bit data:"<<endl;
	for(i=6;i>=0;i--)
		cin>>dat[i];
	transmit(dat);
}
