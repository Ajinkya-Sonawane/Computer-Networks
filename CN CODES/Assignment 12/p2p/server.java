import java.net.*;
import java.util.Scanner;

public class server
{
	public static void main(String args[])
	{
		DatagramSocket ds = null;
		DatagramPacket dp = null;
		InetAddress ip = null;
		String str = null;
		byte buf[] = new byte[1024];
		Scanner scan = new Scanner(System.in);
		
		try
		{
			ds = new DatagramSocket();
			ip = InetAddress.getByName("localhost");
			while(true)
			{
				System.out.print("\nServer : ");
				str = scan.nextLine();
				dp = new DatagramPacket(str.getBytes(),str.length(),ip,1111);
				ds.send(dp);
				if(str.equals("quit"))
					break;
				dp = new DatagramPacket(buf,1024);
				ds.receive(dp);
				str = new String(dp.getData(),0,dp.getLength());
				System.out.println("\nClient : "+str);
				if(str.equals("quit"))
					break;			
			}
			ds.close();
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}
