#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>

using namespace std;

class ace{
	public :
	int cli,a,b,c;
	struct sockaddr_in client;
		ace(){
			cli = socket(PF_INET,SOCK_STREAM,0);
			client.sin_family = AF_INET;
			client.sin_port = htons(9965);
			client.sin_addr.s_addr = inet_addr("127.0.0.1");
			if(connect(cli,(struct sockaddr *)&client,sizeof(client))<0){
				cout<<"\nConnection Failed\n";
				exit(0);
			}
			cout<<"\nConected OK\n";
		
		}
		
		void snd(string s){
			int len = s.length();
			if(send(cli,&s[0],len,0)<0){
				cout<<"\nSend Failed : "<<s<<endl;
				exit(0);
			}
			
		}
		void sndInt(int *s){
			if(send(cli,s,sizeof(int),0)<0){
				cout<<"\nSend Failed : "<<s<<endl;
				exit(0);
			}
			
		}
		void sndDouble(double *s){
			if(send(cli,s,sizeof(double),0)<0){
				cout<<"\nSend Failed : "<<s<<endl;
				exit(0);
			}
			
		}
		
		void recvString(char *ch){
			if(recv(cli,ch,50,0)<0){
				cout<<"\nReciving Failed\n";
			}
		}
		
		
		void recvInt(int *r){
			if(recv(cli,r,sizeof(int),0)<0){
				cout<<"\nReciving Failed\n";
			}
		}
		void recvDou(double *r){
			if(recv(cli,r,sizeof(double),0)<0){
				cout<<"\nReciving Failed\n";
			}
		}
		void cl(){
			shutdown(cli,2);
			
		}
		
};


int main()
{
	ace a;
	char ch[50];
	a.recvString(ch);
	cout<<ch<<endl;
	int choice,op,i,j,k,l;
	double angle,ans=0;
	cin>>choice;
	a.sndInt(&choice);
	cout<<"\nEnter Angle  ";
	cin>>angle;
	a.sndDouble(&angle);
	a.recvDou(&ans);
	cout<<"\nAns Is"<<ans;
	a.cl();
}
