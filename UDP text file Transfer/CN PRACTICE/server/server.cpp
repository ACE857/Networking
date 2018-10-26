#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>

using namespace std;
class ace{
	public :
	int sock,a,b,c;
	struct sockaddr_in port;
	socklen_t len;
	string filecon;
	
		ace(){
			sock = socket(PF_INET,SOCK_DGRAM,0);
			if(sock<0){
				cout<<"\nSocket Creation Failed";
				exit(0);
			}
			cout<<"\nSocket Created Succesfully\n";
			port.sin_family = AF_INET;
			port.sin_port = htons(9999);
			port.sin_addr.s_addr = htonl(INADDR_ANY);
			if(bind(sock,(struct sockaddr *)&port,sizeof(port))<0){
				cout<<"\nBind Failed\n";
				exit(0);
			}
			cout<<"\nBIND SUCESS\n";
			len = sizeof(port);
			
		}
		
		void snd(){
			char msg[50]={0};
			if(recvfrom(sock,&msg[0],50,0,(struct sockaddr *)&port,&len)<0){
				cout<<"\nReciving Failed\n";
				exit(0);
			}
			cout<<"\nRecived file name : "<<msg<<endl;
			
			ifstream ifl;
			ifl.open(msg);
			char str[50];
			ifl.getline(str,50);
			ifl.close();
			if(sendto(sock,&str[0],strlen(str),0,(struct sockaddr *)&port,len)<0){
				cout<<"\nSend Failed\n";
				exit(0);
			}
			cout<<"\nsend : "<<msg;
		}
		
		void readFile(){
			
		}
		
		

};

int main()
{
	ace a;
	a.snd();
}
