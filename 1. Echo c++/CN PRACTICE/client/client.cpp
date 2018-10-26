/*
	1. create socket 
	2. establish conection
	3. send and recive messages
*/
#include<bits/stdc++.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
using namespace std;

class ace{
	public :
		struct sockaddr_in cli,ser;
		int sock;
		ace(){
			sock = socket(PF_INET,SOCK_STREAM,0);
			cli.sin_family = AF_INET;
			cli.sin_port = htons(9883);
			cli.sin_addr.s_addr = inet_addr("127.0.0.1");
			if(connect(sock,(struct sockaddr *)&cli,sizeof(cli))<0){
				cout<<"\nConnection Failed\n";
				exit(0);
			}
			cout<<"\nConnection Established\n";
		}
		
		void snd(){
			char msg[50]={0};
			cout<<"\nEnter Message : ";	cin>>msg;
			
			int len = strlen(msg);
			
			if(send(sock,msg,len,0)<0){
				cout<<"\nSend Failed";	
			}
			cout<<"\nSent Succesfully";
		}
		void rec(){
			char msg[50]={0};
			if(recv(sock,msg,50,0)<0){
				cout<<"\nRecive failed\n";
			}
			cout<<msg;
		}
};

int main(){
	ace a;
	a.rec();
	a.snd();
	
}
