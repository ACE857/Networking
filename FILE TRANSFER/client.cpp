#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

long fsize(char *fname){
	FILE *f;
	f = fopen(fname,"rb");
	fseek(f,0,SEEK_END);
	long s = ftell(f);
	fclose(f);
	return s;
}

int main(){
	int a,b,cli;
	struct sockaddr_in s;
	socklen_t len;
	cli = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	s.sin_family = AF_INET;
	s.sin_port = htons(9997);
	s.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(s);
	char fn[10]={0};
	cout<<"\nEnter File Name : ";	cin>>fn;
	if(sendto(cli,fn,strlen(fn),0,(struct sockaddr *)&s,len)<0){
		cout<<"\nSend Failed Name\n";	return 0;
	}
	long siz = fsize(fn);
	if(sendto(cli,&siz,sizeof(siz),0,(struct sockaddr *)&s,len)<0){
		cout<<"\nSend Failed Name\n";	return 0;
	}
	cout<<"\nFile Size : "<<siz<<endl;
	
	FILE *f;
	f = fopen(fn,"rb");
	char *buf[500];
	memset(buf,0,500);
	fread(buf,500,1,f);
	int itr = 1;
	while(itr*500<siz){
		if(sendto(cli,&buf[0],500,0,(struct sockaddr *)&s,len)<0){
			cout<<"\nSend Failed\n";
		}
		memset(buf,0,500);
		fread(buf,500,1,f);
		itr++;
		
	}
	memset(buf,0,500);
	fread(buf,siz%500,1,f);
	if(sendto(cli,&buf[0],siz%500,0,(struct sockaddr *)&s,len)<0){
			cout<<"\nSend Failed\n";
		}
	cout<<"\nFile Sent\n";
	fclose(f);
	shutdown(cli,2);
	
}
