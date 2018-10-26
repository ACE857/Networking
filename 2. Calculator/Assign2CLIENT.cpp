#include<bits/stdc++.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
using namespace std;

class ace
{
	int sock,cli,len,opt;
	struct sockaddr_in ad,serv;
	int op;
	double angle;
	double result;
	public :
		ace()
		{
			sock=cli=len=0;
		}
		void setConnection()
		{
			sock = socket(PF_INET,SOCK_STREAM,0);
			if(sock<0)
			{ cout<<"Socket Failed"; exit(0); }
			serv.sin_family = AF_INET;
			serv.sin_port = htons(9999);
			serv.sin_addr.s_addr = inet_addr("127.0.0.1");
			if(connect(sock,(struct sockaddr *)&serv , sizeof(serv)) < 0)
			{
				cout<<"\nConnect Failed\n"; exit(0);
			}
			cout<<"\nCONNECTED OK\n";
			cout<<"\nTRIGNOMETRIC CALCULATOR\n";
			
		}
		void getinp()
		{
			char ch[50];
			cout<<"\nEnter expresion  ";
			
			if(recv(sock,&ch,50,0) < 0)
			{ cout<<"\nMENU RECIVE FAILEd\n"; }
			cout<<ch;	
			cin>>opt>>angle;
			cout<<opt<<"  "<<angle<<endl;;
			if(send(sock,&opt,sizeof(opt),0) < 0)
			{ cout<<"\nOPERAND SEND FAILED\n"; exit(0); }
			if(send(sock,&angle,sizeof(angle),0) < 0)
			{ cout<<"\nANGLE SEND FAILED\n"; exit(0); }
			
			cout<<"\nDATA SEND SUCESS\n";
			
			if(recv(sock,&result,sizeof(result),0) < 0)
			{
				cout<<"\nRECIVE FAILED\n"; exit(0);
			}
			cout<<"\nDATA RECIVEDS RESULT IS "<<result<<endl;
		shutdown(sock,2);	
		}
		

};

int main()
{
	ace a;
	a.setConnection();
	a.getinp();
}
