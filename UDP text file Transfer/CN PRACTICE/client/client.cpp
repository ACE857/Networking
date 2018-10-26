#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>

using namespace std;

class ace{
	public :
		int sock,a,b,c;
		struct sockaddr_in port;
		socklen_t adrlen;
		ace(){
			sock = socket(PF_INET,SOCK_DGRAM,0);
			port.sin_family = AF_INET;
			port.sin_port = htons(9999);
			port.sin_addr.s_addr = inet_addr("127.0.0.1");
			adrlen = sizeof(port);
			
		}
		
		void snd(){
			
			string str = "a.txt";
			
			if(sendto(sock,&str[0],str.length(),0,(struct sockaddr *)&port,adrlen )<0){
				cout<<"\nsend failed\n";	
				exit(0);
			}
			cout<<"\nSend "<<str;
			
			char msg[50]={0};
			
			if(recvfrom(sock,&msg[0],50,0,(struct sockaddr *)&port,&adrlen)<0){
				cout<<"\nrecived failed\n";
				exit(0);
			}
			cout<<"recived : "<<msg;
			
			
			
		}
		
};

int main(){
	ace a;
	a.snd();
}
