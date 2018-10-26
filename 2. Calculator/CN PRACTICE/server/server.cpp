#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

class ace{
	public :
	int sock,a,choice,cli,sizeServ;
	string menu;
	double angle;
	int op;
	struct sockaddr_in serv;
		ace(){
		menu = "\nTRIGNOMETRIC CALCULATOR\n1.SIN\n2.COS\n3.TAN\n";
		angle=0;
		op=-1;
			sock = socket(PF_INET,SOCK_STREAM,0);
			serv.sin_family = AF_INET;
			serv.sin_port = htons(9965);
			serv.sin_addr.s_addr = htonl(INADDR_ANY);
			if(bind(sock,(struct sockaddr *)&serv,sizeof(serv))<0){
				cout<<"\nBind Failed\n";
				exit(0);
			}
			cout<<"\nBind Succesfull";
			if(listen(sock,3)<0){
				cout<<"\nListining Failed\n";
				exit(0);
			}
			cout<<"\nListining for clients\n";
			sizeServ = sizeof(serv);
			cli = accept(sock,(struct sockaddr *)&serv,(socklen_t *)&sizeServ);
			if(cli<0){
				cout<<"\nClinet Connection Failed\n";
				exit(0);
			}
			cout<<"\nClient Connected\n";
			
		}
		void sndDouble(double *s){
			if(send(cli,s,sizeof(double),0)<0){
				cout<<"\nSend Failed : "<<s<<endl;
				exit(0);
			}
			
		}
		
		void snd(string s){
			int len = s.length();
			if(send(cli,&s[0],len,0)<0){
				cout<<"\nSend Failed : "<<s<<endl;
				exit(0);
			}
			
		}
		void recvInt(int *r){
			if(recv(cli,r,sizeof(int),0)<0){
				cout<<"\nReciving Failed\n";
			}
		}
		void recvDou(double *r){
			if(recv(cli,r,sizeof(double),0)<0){
				cout<<"\nReciving Failed\n";
			}
		}
		
		double calculate(int choi,double angle){
		int i,j,k;
		double result=0;
		cout<<"\nChoice is "<<choi<<"  "<<"angle is  "<<angle;
			switch(choi){
				case 1 : cout<<choi; angle = angle*3.14/180;
			result = sin(angle);	break;
				case 2 : cout<<choi; angle = angle*3.14/180;
			result = cos(angle);	break;
				case 3 : cout<<choi; angle = angle*3.14/180;
			result = tan(angle);	break;
			}
		return result;
		}
		
		void cl(){
			shutdown(sock,2);
			shutdown(cli,2);
		}
};


int main()
{
	ace a;
	a.snd(a.menu);
	a.recvInt(&(a.choice));
	a.recvDou(&(a.angle));
	double ans = a.calculate(a.choice,a.angle);
	a.sndDouble(&ans);
	cout<<"\nAns Calculated and Send\n"<<ans;
	a.cl();
	
}
