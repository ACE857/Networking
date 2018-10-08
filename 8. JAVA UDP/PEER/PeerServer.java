import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;


public class PeerServer {

	public static void main(String[] args) {

		DatagramSocket socket=null;
		try
		{
			socket=new DatagramSocket(8778); //server socket
			
			byte[] buffer=new byte[1000]; //buffer for msg
			
			DatagramPacket incomingPacket=new DatagramPacket(buffer, buffer.length); //packet to receive data
			
			System.out.println("Server Socket Created.\nWaiting for data..\n");
			
			while(true)
			{
				socket.receive(incomingPacket);
				 byte[] msg=incomingPacket.getData();
				 
				 String s=new String(msg,0,msg.length);
				 
				 System.out.println(incomingPacket.getAddress().getHostAddress()+":"+incomingPacket.getPort()+" > "+s);
				 
				 if(s.equalsIgnoreCase("bye"))
				 {
					 String reply=new String("Bye");
					 msg=reply.getBytes();
					 
					 DatagramPacket sendPacket=new DatagramPacket(msg, msg.length,incomingPacket.getAddress(),incomingPacket.getPort());
					 socket.send(sendPacket);
					 break;
				 }
				 else
				 {
					 BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
					 System.out.print(">");
					 s=br.readLine();
					 msg=s.getBytes();
					 
					 DatagramPacket sendPacket=new DatagramPacket(msg, msg.length,incomingPacket.getAddress(),incomingPacket.getPort());
					 socket.send(sendPacket);
				 }
			}
			socket.close();
		}
		catch(Exception e)
		{
			
		}
	}

}
