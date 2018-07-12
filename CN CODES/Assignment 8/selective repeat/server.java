import java.io.*;
import java.net.*;
class Server
{
	public static void main(String[] args)throws IOException
	{
		int a[]={24,33,60,62,76};
		ServerSocket ss=new ServerSocket(6969);
		Socket s=ss.accept();
		DataInputStream dis=new DataInputStream(s.getInputStream());
		DataOutputStream dos=new DataOutputStream(s.getOutputStream());
		dos.write(a.length);
		int p=a.length;
		for(int i=0;i<p;i++)
		{
			dos.write(a[i]);
			dos.flush();
		}
		int rs=dis.read();
		System.out.println("Resending frame no. " + (rs+1));
		dos.write(a[rs]);
		dos.flush();
		dos.close();
		dis.close();
	}
}
