#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

class ace{
	public :
		int serv,cli;
		struct sockaddr_in s;
		ace(){
			serv = socket(PF_INET,SOCK_STREAM,0);
			s.sin_family = AF_INET;
			s.sin_port = htons(9998);
			s.sin_addr.s_addr = htonl(INADDR_ANY);
			cout<<"\nSocket Created Sucessfully\n";
			if(bind(serv,(struct sockaddr *)&s,sizeof(s))<0){
				cout<<"\nBind Failed\n";
			}
			cout<<"\nBind Sucessfull\n";
			if(listen(serv,3)<0){
				cout<<"\nListen Failed\n";
			}
			cout<<"\nListining for client o.0.o.0.o.......\n";
			socklen_t slen = sizeof(s);
			cli = accept(serv,(struct sockaddr *)&s,(socklen_t *)&slen);
			if(cli<0){
				cout<<"\nConnect Failed\n";
			}
			cout<<"\nClient Connected\n";
			
			
		}
		
		void snd(){
			char msg[50]={0};
			cout<<"\nEnter message : ";	cin>>msg;
			int l = strlen(msg);
			if(send(cli,&msg[0],l,0)<0){
				cout<<"\nSend Failed\n";
			}
		}
		
		void rec(){
			char msg[50]={0};
			if(recv(cli,&msg[0],50,0)<0){
				cout<<"\nReceving Failed\n";
			}
			cout<<msg<<endl;
		}
		void close(){
			shutdown(cli,2);
			shutdown(serv,2);
		}
		void serve(){
			string str = "1.SIN\n2.COS\n3.TAN\n";	
			if(send(cli,&str[0],str.length(),0)<0){
				cout<<"\nSend Failed\n";
			}
			int ch=0;
			if(recv(cli,&ch,sizeof(ch),0)<0){
				cout<<"\nReceving Failed\n";
			}
			cout<<"\nChoice Is "<<ch;
			double ang;
			if(recv(cli,&ang,sizeof(ang),0)<0){
				cout<<"\nReceving Failed\n";
			}
			cout<<"\nAngle Is "<<ang<<endl;
			double rt = tan((3.14*ang)/180);
			
			if(send(cli,&rt,sizeof(rt),0)<0){
				cout<<"\nSend Failed\n";
			}
			
		}

};

int main(){
	ace a;
	int i=3;
	a.serve();
	a.close();
}
