//TODO: Client code for TCP connection and p2p messaging

import java.util.*;
import java.net.*;
import java.io.*;
public class client
{

	//TODO: Declare variables for messages and scanner object
	static String smsg = null;
	static String cmsg = null;
	static Scanner scan = null;
	
	//TODO: Declare input & output stream
	static DataInputStream dis ;
	static DataOutputStream dos ;
	

	
	public static void main(String args[])
	{
		//TODO: Initialize the Scanner object to accept from console
		scan = new Scanner(System.in);
		try
		{
			//TODO: Create a socket to establish connection to server
			Socket sock = new Socket("localhost",12345);
			
			System.out.println("Connected to Server...\n Send a message to Server!!!\n Type to exit the chat");
			
			//TODO:Bind the input and output streams with the socket
			dis = new DataInputStream(sock.getInputStream());
			dos = new DataOutputStream(sock.getOutputStream());
			
			//TODO: Keep the connection alive to send and receive messages
			while(true)
			{
				System.out.print("Client : ");
				cmsg = scan.nextLine();
				
				if(cmsg.equals("quit"))
				{
					System.err.println("\nQuitting.....");
					break;
				}
				//TODO: Send message to Server 
				dos.writeUTF(cmsg);
				
				//TODO: Receive message from Server
				smsg = dis.readUTF();
				System.out.println("Server : "+smsg);
			}
		}
		catch(EOFException e)
		{
			System.err.println("\nServer Disconnected...");
		}
		catch(Exception e)
		{
			System.err.println(e);
		}
	}
}
