import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;
import java.net.UnknownHostException;


public class Client implements Runnable {

	/**
	 * @param args
	 */
	static MulticastSocket clientSocket ;
	static byte[] recvData = new byte[1024];
        static String getsen="hmmm";
        static boolean send_flag=false;
       
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BufferedReader br ;
	
               
		try {
			clientSocket = new MulticastSocket(4447);
			
			InetAddress group = InetAddress.getByName("230.0.0.1");
                        InetAddress IPAddr = InetAddress.getByName("localhost");                        
 
                        clientSocket.joinGroup(group);
			byte[] sendData = new byte[1024];
			
			String sentence=null;
			
		 new Thread(new Client()).start();
		
                         
		//SEND DATA
			while(true)
			{
			sentence=null;
			br	= new BufferedReader(new InputStreamReader(System.in));
                                sentence=br.readLine();  
                           sendData = new byte[1024];  
				sendData = sentence.getBytes();
				DatagramPacket sendPacket = new DatagramPacket(sendData,sendData.length,IPAddr,9877);
				clientSocket.send(sendPacket);
                                send_flag = true;
					
			}

                       // clientSocket.leaveGroup(group);  
			//clientSocket.close();
			
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		

	}

	@Override
	//READ FROM SERVER
	public void run() {
		// TODO Auto-generated method stub
		DatagramPacket recvPacket;
         //  recvPacket = new DatagramPacket(recvData,recvData.length);
            
	   while(!getsen.equals("Bye"))
	   {
		   
		try {
		    	
			//recvPacket = new DatagramPacket(recvData,recvData.length);
                       // clientSocket.receive(recvPacket);
 
                        recvPacket = new DatagramPacket(recvData,recvData.length);
			clientSocket.receive(recvPacket);
			 getsen = new String(recvPacket.getData());
                         if(send_flag!=true)
			 System.out.println("BROADCASTED MESSAGE:"+getsen);
                         getsen= " ";
			 send_flag = false;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
	}
	}

	}
	
	
	


