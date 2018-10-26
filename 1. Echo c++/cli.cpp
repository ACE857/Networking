#include <sys/socket.h>
#include<bits/stdc++.h>
#include <netdb.h>
#include<sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
int main()
{
	struct sockaddr_in address,serv;
	int sock = 0;
	sock = socket(PF_INET,SOCK_STREAM,0);
	if(sock<0) 
	{
		cout<<"\nSocket Failed\n"; return 0;
	}
	serv.sin_family = AF_INET;
	serv.sin_port = htons(9789);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sock,(struct sockaddr *)&serv , sizeof(serv)) < 0)
	{
		cout<<"\nConnect Failed\n"; return 0;
	}
	char ch[] = "HELLO SERVER";
	int cnt = send(sock,ch,strlen(ch),0);
	char buf[50] = {0};
	if(cnt<0) 
	{
		cout<<"\nSend Failed\n";
	}
	cout<<"\nMessage send\n";
	if(recv(sock,buf,50,0)<0)
	{
		cout<<"\nRecive 2 fail\n";
	}
	cout<<"\nRecived Message is - "<<buf;
	shutdown(sock,2);
	return 0;
}
