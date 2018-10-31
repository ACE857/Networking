#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>
using namespace std;

class ace{
	public :
		int serv;
		struct sockaddr_in s;
		ace(){
			serv = socket(PF_INET,SOCK_STREAM,0);
			cout<<"\nSocket Created\n";
			s.sin_family = AF_INET;
			s.sin_port = htons(9998);
			s.sin_addr.s_addr = inet_addr("127.0.0.1");
			
			if(connect(serv,(struct sockaddr *)&s,sizeof(s))<0){
				cout<<"\nUnable To Connect\n";
			}
			cout<<"\nConnection Established\n";
			
		}
		
		void snd(){
			char msg[50]={0};
			cout<<"\nEnter Message : ";	cin>>msg;
			int i,l=strlen(msg);
			if(send(serv,&msg[0],l,0)<0){
				cout<<"\nSend Failed\n";
			}
		}
		
		void rec(){
			char msg[50]={0};
			if(recv(serv,&msg[0],50,0)<0){
				cout<<"\nReceive Failed\n";
			}
			cout<<msg<<endl;
		}
		void close(){
			shutdown(serv,2);
		}
		void serve(){
			char msg[50]={0};
			if(recv(serv,&msg[0],50,0)<0){
				cout<<"\nReceive Failed\n";
			}
			cout<<msg<<endl;
			int ch=0;
			cin>>ch;
			if(send(serv,&ch,sizeof(ch),0)<0){
				cout<<"\nSend Failed\n";
			}
			double ang = 0.0;
			cout<<"\nEnter Angle  :  ";	cin>>ang;
			if(send(serv,&ang,sizeof(ang),0)<0){
				cout<<"\nSend Failed\n";
			}
			if(recv(serv,&ang,sizeof(ang),0)<0){
				cout<<"\nReceving Failed\n";
			}
			cout<<"\nAns Is "<<ang<<endl;
			
		}
};

int main(){
	ace a;
	int i=3;
	a.serve();
	a.close();
	
}
