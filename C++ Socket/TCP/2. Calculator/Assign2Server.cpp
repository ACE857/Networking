#include<bits/stdc++.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
using namespace std;

class ops
{
	public :
		int op,ex;
		double ang,result;
		ops()
		{
			op = ex = 0;
			ang = result = 0.0;
		}
};

class ace
{
	
	int sockid,socklen,cli;
	struct sockaddr_in sockst;
	
	public :
		ace()
		{
			sockid = socklen = cli = 0;
		}
		
		void initsocket()
		{
			sockid = socket(PF_INET,SOCK_STREAM,0);
			if(sockid<0)
			{ cout<<"\nSOCKET FAILED\n"; exit(0); }
			cout<<"\nSOCKET OK\n";
			sockst.sin_family = AF_INET;
			sockst.sin_port = htons(9996);
			sockst.sin_addr.s_addr = htonl(INADDR_ANY);
			if(bind( sockid , (struct sockaddr *) &sockst , sizeof(sockst) )<0)
			{ cout<<"\nBIND FAILED\n"; exit(0); }
			cout<<"\nBIND OK\n";
			socklen = sizeof(sockst);
			if(listen(sockid , 3)< 0)
			{ cout<<"\nLISTEN FAILED\n"; exit(0); }
			cout<<"\nLISTINING FOR CLIENTS .....\n";
			
			cli = accept(sockid , (struct sockaddr *) & sockst , (socklen_t *) & socklen );
			if(cli<0)
			{ cout<<"\nCLIENT CONNECTION FAILED\n"; exit(0); }	
			cout<<"\nCLIENT CONNECTED OK\n";		
		}
		
		void serve()
		{
			ops o;
			double ang,ans;
			int op;
			while(true)
			{	int cnt = recv(cli,&ang,sizeof(ang),0);
				chk(cnt);
				cnt = recv(cli,&op,sizeof(op),0);
				chk(cnt);
				cout<<"\nSERVING REQUEST - "<<ang<<"  "<<op<<endl;;
				ans = findANS(ang,op);
				if(send(cli,&ans,sizeof(ans),0)<0)
				{ cout<<"\nSEND FAILED\n"; exit(0);}
				cout<<"\nRESULT SENT\n";
			}	
			
		}
		
		void chk(int x)
		{
			if(x<0) cout<<"\nRECIVE FAILED\n";
		}
		
		double findANS(double angle, int op)
		{
			//angle*=0.0174533;
			//cout<<endl<<angle<<endl;
			double result = 0.0;
			angle = angle*3.14/180;
			result = sin(angle);
			return result;
		}
		
};
int main()
{
	ace a;
	a.initsocket();
	a.serve();
	
	
}





