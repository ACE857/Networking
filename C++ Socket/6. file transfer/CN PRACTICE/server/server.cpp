#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

class ace{
	public :
		int sock,a,b,c,d;
		struct sockaddr_in port;
		socklen_t len;
		ace(){
			sock = socket(PF_INET,SOCK_DGRAM,0);
			port.sin_family = AF_INET;
			port.sin_port = htons(9997);
			port.sin_addr.s_addr = inet_addr("127.0.0.1");
			len = sizeof(port);
			cout<<"\nServer UP and running \n";
			
		}
		void s(){
			string str;
			cout<<"\nEnter FileName : ";
			cin>>str;
			if(sendto(sock,&str[0],str.length(),0,(struct sockaddr*)&port,len)<0){
				cout<<"\nSend Failed\n";
				exit(0);
			}
			cout<<"\nFile name Send\n";
			
			char *buf = new char[100000000];
			bzero((char *)buf,sizeof(buf));
			
			if(recvfrom(sock,buf,100000000,0,(struct sockaddr *)&port,&len)<0){
				cout<<"\nFile reciving failed\n";
				exit(0);
			}
			
			fstream fst;
			fst.open(&str[0],ios::out|ios::binary);
			fst.write(buf,strlen(buf));
			cout<<"\nFile Recived\n";
			
			
		}
		
};

int main(){
	ace a;
	a.s();
}
