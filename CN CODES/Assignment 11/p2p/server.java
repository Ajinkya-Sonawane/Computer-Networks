//TODO: Server code for TCP connection and p2p messaging

import java.util.*;
import java.net.*;
import java.io.*;

public class server
{
	//TODO:Declare variables for messages and object for scanner 
	static String smsg = null;
	static String cmsg = null;
	static Scanner scan = null;
	
	static DataInputStream dis ;
	static DataOutputStream dos ;
	
	
	public static void main(String args[])
	{
		//TODO:Initialize the Scanner object to accept input from Console
		scan = new Scanner(System.in);
		try
		{
			//TODO: Create a server socket using port number
			ServerSocket ss = new ServerSocket(12345);
			
			//TODO: Create a socket which will hold the connection accepted by ServerSocket
			Socket sock = ss.accept();
			System.out.println("Connection established with : "+sock.getRemoteSocketAddress()+"\nType quit to exit chat.....\n Waiting for message from client.....");
			
			//TODO: Bind the input and output streams with the socket
			dis = new DataInputStream(sock.getInputStream());
			dos = new DataOutputStream(sock.getOutputStream());
			
			//TODO: Keep the connection alive to send and receive messages
			while(true)
			{
				//TODO: Accept message from client
				cmsg = dis.readUTF();
				System.out.println("Client :  "+cmsg);			
				
				System.out.print("Server : ");
				smsg = scan.nextLine();
				if(smsg.equals("quit"))
				{
					System.err.println("\nQuitting.....");
					break;
				}
				//TODO: Send message to client
				dos.writeUTF(smsg);
			}
			
		}
		catch(EOFException e)
		{
			System.err.println("\nClient Disconnected...");
		}
		catch(Exception e)
		{
			System.err.print(e);
		}
	}
}
