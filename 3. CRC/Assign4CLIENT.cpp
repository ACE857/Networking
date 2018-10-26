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
			serv.sin_port = htons(9997);
			serv.sin_addr.s_addr = inet_addr("127.0.0.1");
			if(connect(sock,(struct sockaddr *)&serv , sizeof(serv)) < 0)
			{
				cout<<"\nConnect Failed\n"; exit(0);
			}
			cout<<"\nCONNECTED OK\n";
			
		}
		void getinp()
		{
		
		//if(recv(sock,&ch,50,0) < 0)
		char crc[50]={0};
		char data[50]={0},tmp[50]={0};
		cout<<"\nEnter CRC  ";	cin>>crc;
		cout<<"\nEnter Data  "; cin>>data;
		strcpy(tmp,data);
		int i,j,k,l,m=strlen(crc),n=strlen(data);
		for(i=n;i<n+m-1;i++)	data[i]='0';
		cout<<"\nData1  "<<data;
		i=0;	l=m+n-1;
		
		while(i+m<l)
		{
			while(data[i]!='1') i++;
			for(j=i,k=0; i+m-1<l && k<m && j<l ;j++,k++)
			{
				if(data[j]==crc[k]) data[j]='0'; 	else data[j]='1';
			}
			cout<<"\n"<<data;
		}
		cout<<"\nRem  "<<data;
		for(i=n;i<n+m-1;i++)	tmp[i]=data[i];
		cout<<"\nDATA IS "<<tmp;
		if(send(sock,&tmp,l,0) < 0)
		{
			cout<<"\nSend Failed :-<  \n";
		}
		
			
		shutdown(sock,2);	
		}
		

};

int main()
{
	ace a;
	a.setConnection();
	a.getinp();
}
