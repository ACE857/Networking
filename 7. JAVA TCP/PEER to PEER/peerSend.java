import java.io.*;
import java.util.*;
import java.net.*;
//client
public class peerSend implements Runnable
{
	Socket sock;
	InputStreamReader ir;
	BufferedReader br;
	PrintWriter pr;
	String id;
	Scanner sc;
	static peerSend p;
	public static void main(String args[])
	{
		p = new peerSend();
		try
		{
			
			System.out.print("\nEnter User ID - ");
			p.sc = new Scanner(System.in);
			p.id = p.sc.next();
			
			p.sock = new Socket("127.0.0.1",9999);
			p.ir = new InputStreamReader(p.sock.getInputStream());
			p.br = new BufferedReader(p.ir);
			p.pr = new PrintWriter(p.sock.getOutputStream());
			System.out.print(""+p.br.readLine());
			
			p.pr.println("Welcome :-)");
			p.pr.flush();
			
			Runnable lis = new peerSend();
			Thread t1 = new Thread(lis);
			t1.start();
			
			snd();
			
			
			
			p.pr.close();
			p.br.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	static void snd()
	{
	
	try{
		String msg;
		while(true)
		{
			//System.out.println("snd active\n");
			System.out.print("\n"+p.id+" >> ");
			msg = p.sc.nextLine();
			msg = p.id+" >> "+msg;
			p.pr.println(""+msg);	
			p.pr.flush();
		}
	}
	catch(Exception e)
	{
		System.out.println(e.getMessage());
	}
	}
	
	public void run()
	{
		
	try{
		String msg;
		while(true)
		{
			//System.out.println("run active\n");
			 msg = p.br.readLine();
			if(msg.equals("bye")) System.exit(0);
			System.out.println("\n"+msg);
		}
	}
	catch(Exception e)
	{
		System.out.println(e.getMessage());
	}
	}
	
	
}

