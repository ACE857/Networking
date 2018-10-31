/*
	Anuj Singh 3315
*/

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

void die(char *s)
{
	perror(s);
	exit(1);
}

int main(void)
{
	struct sockaddr_in si_me, si_other;
	int s, i,j, slen = sizeof(si_other) , recv_len;
	char buf[503];
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	memset((char *)&si_me,0,sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(8885);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if( bind(s,(struct sockaddr*)&si_me,sizeof(si_me)) == -1)
	{
		die("bind");
	}
	char fname[20];
	FILE *fp;
	recv_len = recvfrom(s,buf,20,0,(struct sockaddr *)&si_other,(socklen_t*)&slen);
	char fna[100];
	strcpy(fna,buf);
	int len= strlen(fna);
	fna[len+1]='\0';
	for(j=len-1;j>=0;j--)
	{
		if(fna[j]=='.')
		{
			fna[j+1]=fna[j];
			fna[j]='1';
			break;
		}
		else
			fna[j+1]=fna[j];
	}
	memset(buf,0,503);
	recv_len = recvfrom(s,buf,20,0,(struct sockaddr *)&si_other,(socklen_t*)&slen);
	long mm = atoi(buf);
	fp=fopen(fna,"wb");
	int itr=1;
	memset(buf,0,503);
	while(itr*503<mm)
	{
		if((recv_len = recvfrom(s, buf, 503, 0, (struct sockaddr *) &si_other,(socklen_t*) &slen)) == -1)
		{
			die("recvfrom()");
		}
		fwrite(buf,503, 1, fp);
		memset(buf,0,503);
		itr++;
	}
	recv_len = recvfrom(s,buf,(mm%503),0,(struct sockaddr*)&si_other,(socklen_t*)&slen);
	fwrite(buf,(mm%503),1,fp);
	memset(buf,0,503);
	fclose(fp);
	return 0;
}
