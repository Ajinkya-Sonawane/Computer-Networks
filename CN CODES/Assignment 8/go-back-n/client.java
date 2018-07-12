import java.io.*;
import java.net.*;
class Client
{
	public static void main(String[] args)throws IOException
	{
		Socket s=new Socket("localhost",6969);
		DataInputStream dis=new DataInputStream(s.getInputStream());
		DataOutputStream dos=new DataOutputStream(s.getOutputStream());
		int p=dis.read();
		int arr[]=new int[p];
		int i;
		for(i=0;i<p;i++)
			arr[i]=dis.read();
		arr[2]=-1;
		for(i=0;i<p;i++)
		{
			if(arr[i]==-1)
			{
				System.out.println("Requesting for frame no. " + (i+1) + " to be sent again");
				dos.write(i);
				dos.flush(); 
			}
		}
		for(i=2;i<p;i++)
		{
			arr[i]=dis.read();
		}
		System.out.println("Complete frame:");
		for(i=0;i<p;i++)
			System.out.print(arr[i]+"\t");
		System.out.println();
		dos.close();
		dis.close();
	}
}
