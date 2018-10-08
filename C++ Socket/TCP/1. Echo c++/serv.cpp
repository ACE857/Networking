#include <sys/socket.h>
#include<bits/stdc++.h>
#include <netdb.h>
#include<sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;
int main()
{
	int sockid = socket(PF_INET,SOCK_STREAM,0);
	if(sockid<0)
	{
		cout<<"\nSocket Failed\n";	return 0;
	}
	cout<<"\nSocked Created OK\n";
	struct sockaddr_in addport;
	addport.sin_family = AF_INET;
	addport.sin_port = htons(9789);
	addport.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockid, (struct sockaddr *)&addport , sizeof(addport))==-1)
	{
		cout<<"\nBind Failed\n";	return 0;
	}
	cout<<"\nBind Created OK\n";
	if( listen(sockid , 3)<0)
	{
		cout<<"\nListen Failed\n";	return 0;
	}
	cout<<"\nListen OK\n";
	int adrlen = sizeof(addport);
	int cli = accept(sockid,(struct sockaddr *)&addport,(socklen_t *) & adrlen );
	if(cli<0)
	{
		cout<<"\nAccept failed\n"; return 0;
	}
	cout<<"\nClient Accepted OK\n";
	char buf[50] = {0};
	int cnt = recv(cli,buf,50,0);
	if(cnt<0) {cout<<"\nRecive Failed\n"; return 0;}
	cout<<"\nMessage Recived - "<<buf;
	//cout<<"\nEnter Message  ";
	//cin>>buf;
	if(send(cli,buf,strlen(buf),0)<0) 
	{ 
		cout<<"\nSend Failed\n";
	}
	cout<<"\nSend Sucess\n";
	shutdown(sockid,2);
	return 0;
	
}
