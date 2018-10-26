/*
	1 include header
	2. create socket
	3.bind socket
	3. listen for connections
	4. accept connections
	5. send or recive messages

*/
#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;

class ace{
	public :
	int sockid,addrlen,cli,c;
	struct sockaddr_in addrport;
	ace(){
		sockid = socket(PF_INET,SOCK_STREAM,0);
		if(sockid<0){
			cout<<"\nSocket Creation Failed\n";
			exit(0);
		}
		cout<<"Socket Created\n";
		addrport.sin_family = AF_INET;
		addrport.sin_port = htons(9883);
		addrport.sin_addr.s_addr = htonl(INADDR_ANY);
		
		if(bind(sockid,(struct sockaddr *)&addrport,sizeof(addrport))==-1)
		{
			cout<<"\nSocket Bind Failed\n";
			exit(0);
		}
		cout<<"\nSocked Binded\n";
		
		if(listen(sockid,3)<0){
			cout<<"\nListen Failed\n";
			exit(0);
		}
		cout<<"\nListnening For Clients\n";
		int addrlen = sizeof(addrport);
		cli = accept(sockid,(struct sockaddr *)&addrport,(socklen_t *)&addrlen);
		if(cli<0){
			cout<<"\nClient Connection Failed";
			exit(0);
		}
		cout<<"\nClient Accepted\n";
	}
	
	void snd(){
	
		char msg[50];
		cout<<"Enter message : ";
		cin>>msg;
		int len = strlen(msg);
		if(send(cli,msg,len,0)<0){
			cout<<"\nMessage send failed\n";
		}
	}
	void rec(){
		char msg[50]={0};
		if(recv(cli,msg,50,0)<0){
			cout<<"\nRecv failed\n";
			exit(0);
		}
		cout<<msg;
	}
	
};

int main(){
	
	ace a;
	a.snd();
	a.rec();
		
	
}
