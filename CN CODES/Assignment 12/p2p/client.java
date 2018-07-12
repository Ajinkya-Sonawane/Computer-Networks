import java.net.*;
import java.util.Scanner;

public class client
{
	public static void main(String args[])
	{
		DatagramSocket ds = null;
		DatagramPacket dp = null;
		InetAddress ip = null;
		String str = null;
		byte buf[] = new byte[1024];
		Scanner scan = new Scanner(System.in);
		SocketAddress host = null;
		try
		{
			ds = new DatagramSocket(1111);
			while(true)
			{
				dp = new DatagramPacket(buf,1024);
				ds.receive(dp);
				str = new String(dp.getData(),0,dp.getLength());
				System.out.println("\n"+dp.getSocketAddress().toString()+str);
				if(str.equals("quit"))
					break;

				System.out.print("\nYour Message : ");
				str = scan.nextLine();
				ds.send(new DatagramPacket(str.getBytes(),str.length(),
((InetSocketAddress)dp.getSocketAddress()).getAddress(),((InetSocketAddress)dp.getSocketAddress()).getPort()));
				
			}
			ds.close();
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}
