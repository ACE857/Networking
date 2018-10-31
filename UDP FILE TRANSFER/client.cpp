#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
using namespace std;

void die(char *s)
{
	perror(s);
	exit(1);
}
unsigned long fsize(char* file)
{
	FILE * f = fopen(file, "r");
	fseek(f, 0, SEEK_END);
	long len = (long)ftell(f);
	fclose(f);
	return len;
}

int main(void)
{
	struct sockaddr_in si_other;
	int s,i,slen=sizeof(si_other);
	char buf[503];
	char message[503];
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(8885);
	if (inet_aton("127.0.0.1",&si_other.sin_addr) == 0) 
	{
		fprintf(stderr,"inet_aton() failed\n");
		exit(1);
	}
	char fname[20];
	cout<<"Enter Filename : ";
	cin>>fname;
	sendto(s,fname,20,0,(struct sockaddr *)&si_other, slen);
	memset(message,0,503);
	long siz = fsize(fname);
	char str[10];
	sprintf(str, "%d", siz);
	sendto(s,str,20,0,(struct sockaddr *)&si_other, slen);
	FILE *f;
	f=fopen(fname,"rb");
	memset(message,0,503);
	fread(message, 503,1,f);
	int itr =1;
	while(itr*503<siz)
	{
		if (sendto(s, message, 503 , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
			die("sendto()");
		}
		memset(message,0,503);
		fread(message, 503,1,f);
		itr++;
	}
	fread(message, (siz % 503),1,f);
	sendto(s, message, (siz % 503) , 0 , (struct sockaddr *) &si_other, slen);
	memset(message,0,503);
	fclose(f);
	return 0;
}
