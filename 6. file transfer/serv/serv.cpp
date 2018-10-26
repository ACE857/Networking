#include <iostream>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;

#define PORT 9999
int main() {

	sockaddr_in server_addr,client_addr;

	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
		exit(1);
	else
		cout<<"Socket Created.";
	bzero((char *)&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);

	if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
		exit(1);

	if(listen(sock,10)<0)
	{
		exit(1);
	}
	socklen_t socklen=sizeof(client_addr);

	int newSocket=accept(sock,(struct sockaddr*)&client_addr,&socklen);
	if(newSocket<0)
		exit(1);
	else
		cout<<"\nCONNECTION ACCEPTED";
	long long int msg_len;


		cout<<"\nENter Filename:";
		char filename[100];
		cin>>filename;
		cout<<filename;
		fstream fout;



		msg_len=send(newSocket,filename,100,0); 
		if(msg_len==-1)
			exit(1);

		fout.open(filename,ios::in|ios::out|ios::binary);
				fout.seekg(0,ios::end);
				long long int filesize=fout.tellg();
				char *filebuff=new char[filesize];
				fout.seekg(0,ios::beg);
				fout.read(filebuff,filesize); 



		msg_len=send(newSocket,filebuff,filesize,0);
		if(msg_len==-1)
			exit(1);
		else
			cout<<"Transmission Successful";
		fout.close();
	
	return 0;
}
