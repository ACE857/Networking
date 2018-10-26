#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

class ace{
	public :
		int sock,a,b,c;
		struct sockaddr_in port;
		socklen_t len;
		ace(){
			/*sock = socket(PF_INET,SOCK_DGRAM,0);
			port.sin_family = AF_INET;
			port.sin_port = htons(9997);
			port.sin_addr.s_addr = htonl(INADDR_ANY);
			if(bind(sock,(struct sockaddr *)&port,sizeof(port))<0){
				cout<<"\nsocket bind failed";
				exit(0);
			}
			cout<<"\nSocket binded\n";
			
			len = sizeof(port);
			cout<<"\nServer Up and running\n";*/
		}
		
		void s(){
			/*char fn[20]={0};
			cout<<"\nWaiting for file name\n";
			if(recvfrom(sock,fn,20,0,(struct sockaddr *)&port,&len)<0){
				cout<<"\nFile Name Recive failed\n";
				exit(0);
			}
			cout<<"\nfilename : "<<fn;*/
			fstream fout;
			fout.open("v.mp4",ios::in|ios::out|ios::binary);
				fout.seekg(0,ios::end);
				long long int filesize=fout.tellg();
				char *buf=new char[filesize];
				fout.seekg(0,ios::beg);
				cout<<fout.tellg();
				fout.read(buf,filesize); 
		cout<<"\nFileSize is : "<<filesize<<endl;
		cout<<"\nBuffSize is : "<<strlen(buf)<<endl;
			//cout<<"\nFile Name is : "<<fn;
		/*	if(sendto(sock,buf,filesize,0,(struct sockaddr*)&port,len)<0){
				cout<<"file send failed";
				exit(0);
			}*/
		}
		

};

int main(){
	ace a;
	a.s();
}
