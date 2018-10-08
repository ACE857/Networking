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
			sockst.sin_port = htons(9997);
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
			shutdown(sockid,2);
		}
		
		void serve()
		{
			
	//cnt = recv(cli,&ang,sizeof(ang),0);
				
			char crc[50]={0};
		char data[50]={0},tmp[50]={0};
		cout<<"\nEnter CRC  ";	cin>>crc;

		if(recv(cli,&data,50,0) < 0 )

		strcpy(tmp,data);
		int i,j,k,l,m=strlen(crc),n=strlen(data);
		
		cout<<"\nData RECIVED  "<<data;
		i=0;	l=m+n-1;
		cout<<"\n1.ERROR FREE\n2.WITH ERROR  "; cin>>i;
		if(i==1)
		{ i=0;
		while(i+m<n)
		{
			while(data[i]!='1') i++;
			for(j=i,k=0;i+m-1<n && k<m && j<n ;j++,k++)
			{
				if(data[j]==crc[k]) data[j]='0'; 	else data[j]='1';
			}
		}
				cout<<"\nREMAINDER  "<<data;
				for(i=0;i<strlen(data);i++) { if(data[i]=='1')  {cout<<"\nErr DATA CORRUPTED"; shutdown(sockid,2); exit(0);}}
				 cout<<"\nVOla DATA CORRECT";
			}
			else if(i==2){	i=0;
		strcpy(data,tmp);
		srand(time(0));
		int lt = abs(rand()%n);
		cout<<endl<<lt<<endl;
		data[3] = data[3]=='1'?'0':'1';
		cout<<tmp<<"what"<<endl;
		while(i+m<n)
		{
			while(data[i]!='1') i++;
			for(j=i,k=0;i+m-1<n && k<m && j<n ;j++,k++)
			{
				if(data[j]==crc[k]) data[j]='0'; 	else data[j]='1';
			}
		}
				cout<<"\nREMAINDER  "<<data;
				cout<<tmp<<"  "<<strlen(tmp)<<endl;
				for(i=0;i<n;i++) {if(data[i]=='1')  {cout<<"\nErr DATA CORRUPTED"; shutdown(sockid,2); exit(0);}}
				 cout<<"\nVOla DATA CORRECT";
				
		}
			
			shutdown(sockid,2);
			
		}
		
		
		
};
int main()
{
	ace a;
	a.initsocket();
	a.serve();
	
	
}





