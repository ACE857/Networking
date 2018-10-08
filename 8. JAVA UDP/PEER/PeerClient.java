import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class PeerClient {

public final static int  PORT=8778;
public final static String SERVER_IP="127.0.0.1";
	public static void main(String[] args) {
		BufferedReader br=null;
		DatagramSocket socket=null;
		String s;
		try {
			
			socket=new DatagramSocket();
			br=new BufferedReader(new InputStreamReader(System.in));
			
			InetAddress server=InetAddress.getByName(SERVER_IP);
			System.out.println("Client Socket Created.\nENter msg:");
			while(true)
			{
				System.out.print(">");
				s=br.readLine();
				byte[] sendMsg=s.getBytes();
				
				DatagramPacket sendingPacket=new DatagramPacket(sendMsg, sendMsg.length,server,PORT);
				socket.send(sendingPacket);
				System.out.println("Waiting for reply.");
				
				byte[] replyMsg=new byte[1000];
				
				DatagramPacket receivingPacket=new DatagramPacket(replyMsg, replyMsg.length);
				socket.receive(receivingPacket);
				 byte[] data=receivingPacket.getData();
				 String s1=new String(data, 0,data.length);
				 System.out.println(receivingPacket.getAddress().getHostAddress()+":"+receivingPacket.getPort()+"=> "+s1);
			
				 if(s1.equalsIgnoreCase("bye"))
				 {
					 System.out.println("Connection Closed");
					 break;
				 }
			
			}
			socket.close();
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
}
