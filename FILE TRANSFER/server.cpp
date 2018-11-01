#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;



int main(){
	struct sockaddr_in s;
	int serv;
	socklen_t len;
	serv = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	s.sin_family = AF_INET;
	s.sin_port = htons(9997);
	s.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(s);
	if(bind(serv,(struct sockaddr *)&s,sizeof(s))<0){
		cout<<"\nBind Failed\n";
	}
	cout<<"\nBind Sucessfull\n";
	char fn[10]={0};
	if(recvfrom(serv,&fn[0],10,0,(struct sockaddr *)&s,&len)<0){
		cout<<"\nReceive Failed\n";
		exit(0);
	}
	cout<<"\nFile Name : "<<fn<<endl;
	long siz = 0;
	
	if(recvfrom(serv,&siz,sizeof(siz),0,(struct sockaddr *)&s,&len)<0){
		cout<<"\nReceive Failed\n";
		exit(0);
	}
	cout<<"\nFile Size : "<<siz<<endl;
	
	FILE *f;
	f = fopen(fn,"wb");
	int itr=1;
	char buf[500];
	memset(buf,0,500);
	while(itr*500<siz){
		if(recvfrom(serv,&buf[0],500,0,(struct sockaddr *)&s,&len)<0){
			cout<<"\nReceive Failed\n";
		}
		fwrite(buf,500,1,f);
		memset(buf,0,500);
		itr++;
	}
	if(recvfrom(serv,&buf[0],siz%500,0,(struct sockaddr *)&s,&len)<0){
			cout<<"\nReceive Failed\n";
		}
		fwrite(buf,siz%500,1,f);
		memset(buf,0,500);
	cout<<"\nFile Received\n";
	fclose(f);
	shutdown(serv,2);
	
}
