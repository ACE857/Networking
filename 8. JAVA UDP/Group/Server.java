import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;




public class Server  {

	/**
	 * @param args
	 */
	static byte[] recvData = new byte[1024];
	static byte[] sendData = new byte[1024];
	static DatagramSocket ds;
	static   InetAddress group;
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			 ds = new DatagramSocket(9877);
                       group = InetAddress.getByName("230.0.0.1");
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                   
                     DatagramPacket recvPack;
		while(true)
		{
		recvData = new byte[1024];
			try {
                                
				recvPack = new DatagramPacket(recvData,recvData.length);
				ds.receive(recvPack);
				String sentence = new String(recvPack.getData());
				System.out.println(sentence);
				method(sentence);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
					
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
}

	

	public static void method(String sentence) {
		// TODO Auto-generated method stub
              
		sendData = sentence.getBytes();
		DatagramPacket sendPack = new DatagramPacket(sendData,sendData.length,group,4447);
		try {
			ds.send(sendPack);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
