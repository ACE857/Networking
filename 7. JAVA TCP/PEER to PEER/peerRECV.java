import java.io.*;
import java.util.*;
import java.net.*;
// server
public class peerRECV implements Runnable
{
	ServerSocket sock;
	Socket cli;
	InputStreamReader ir;
	BufferedReader br;
	PrintWriter pr;
	String id;
	Scanner sc;
	static peerRECV p ;
	public static void main(String args[])
	{
		p = new peerRECV();
		p.sc = new Scanner(System.in);
		System.out.print("\nEnter You User ID - ");
			p.id = p.sc.next();
		try{
			
			
			p.sock = new ServerSocket(9999);
			System.out.print("\nWaiting For SomeOne ... ");
			p.cli = p.sock.accept();
			p.ir = new InputStreamReader(p.cli.getInputStream());
			p.br = new BufferedReader(p.ir);
			p.pr = new PrintWriter(p.cli.getOutputStream());
			
			
			
			
			
			p.pr.println(p.id+"Connected :-)");
			p.pr.flush();
			
			System.out.println(""+p.br.readLine());
			
			Runnable lis = new peerRECV();
			Thread t1 = new Thread(lis);
			t1.start();
			
			snd();
				
			p.pr.close();
			p.br.close();
		}
		catch(Exception e)
		{
			System.out.println("\n"+e.getMessage());
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
			msg = p.sc.next();
			msg = p.id+" >> "+msg;
			p.pr.println(msg);	
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

