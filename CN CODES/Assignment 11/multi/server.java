import java.util.*;
import java.net.*;
import java.io.*;

public class server extends Thread
{
	//TODO: Declare variables for messages and scanner object
	String smsg = null;
	Scanner scan = null;
	Socket sock = null;
	static ArrayList<Socket> client_list = new ArrayList<>();
	
	//TODO: Input and output streams to send & recieve messages
	DataInputStream dis = null;
	DataOutputStream dos = null;
	
	//TODO: Constructor
	public server(Socket sock)
	{
		//TODO: Initialize the socket with the client socket
		this.sock = sock;
		
		//TODO: Initialize the Scanner class to accept input from console
		scan = new Scanner(System.in);
	}
	
	
	@Override
	public void run()
	{
		try
		{
			//TODO: Initialize the input & output streams with the client socket
			dis = new DataInputStream(sock.getInputStream());
			dos = new DataOutputStream(sock.getOutputStream());
		
			//TODO: Receive client messages
			while(true)
			{
				String cmsg = dis.readUTF();
				System.out.println("Client "+client_list.indexOf(this.sock)+" : "+cmsg);
			}
		}
		catch(Exception e)
		{
			System.out.println(e);
			
			//TODO: If client is disconnected then remove itz socket object from the client list
			System.out.println("\n Client "+client_list.indexOf(this.sock)+" removed.");
			client_list.remove(client_list.indexOf(this.sock));
		}
	}
	public static void main(String args[])
	{
		try
		{
			ServerSocket ss = new ServerSocket(1234);
			while(true)
			{
				Socket sock = ss.accept();
				server.client_list.add(sock);
				new server(sock).start();
			}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}
