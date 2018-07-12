#include<iostream>
using namespace std;
int main()
{
	int ds,divs;
	cout<<"Enter the size of your data unit:"<<endl;
	cin>>ds;
	cout<<"Enter the size of the divisor:"<<endl;
	cin>>divs;
	int size=ds+divs-1;
	bool data[size];
	bool temp[size];
	bool divisor[divs];
	int i,j;
	cout<<"Enter the data:"<<endl;
	for(i=0;i<ds;i++)
	{
		cin>>data[i];
		temp[i]=data[i];
	}

	for(i=ds;i<size;i++)
	{
		temp[i]=0;
		data[i]=0;
	}
	cout<<"Enter the divisor:"<<endl;
	for(i=0;i<divs;i++)
	{
		cin>>divisor[i];
	}
	for(i=0;i<ds;i++)
	{
		if(temp[i]==0)
			continue;
		for(j=0;j<divs;j++)
		{
			if(temp[i+j]==divisor[j])
				temp[i+j]=0;
			else
				temp[i+j]=1;
		}		
	}
	cout<<"Remainder="<<endl;
	for(i=ds;i<size;i++)
		cout<<temp[i];
	for(i=ds;i<size;i++)
	{
		data[i]=temp[i];
	}
	cout<<"\nData after performing crc=:"<<endl;
	for(i=0;i<size;i++)
		cout<<data[i];
	cout<<"\nChecking data on receiver's side..."<<endl;
	for(i=0;i<ds;i++)
	{
		if(data[i]==0)
			continue;
		for(j=0;j<divs;j++)
		{
			if(data[i+j]==divisor[j])
				data[i+j]=0;
			else
				data[i+j]=1;
		}		
	}
	cout<<"Remainder="<<endl;
	for(i=ds;i<size;i++)
		cout<<data[i];
	
}
