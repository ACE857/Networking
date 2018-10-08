#include <bits/stdc++.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>


#include <pcap.h>
using namespace std;

int icmpCount = 0;
int tcpCount = 0;
int udpCount = 0;
int dnsCount = 0;


void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {

    const struct ether_header* ethernetHeader;
    const struct ip* ipHeader;
    const struct tcphdr* tcpHeader;
    const struct udphdr* udpHeader;
    char sourceIP[INET_ADDRSTRLEN];
    char destIP[INET_ADDRSTRLEN];
    u_int sourcePort, destPort;
    u_char *data;	
    int dataLength = 0;
    int i;
    
  string dataStr = "";

    ethernetHeader = (struct ether_header*)packet;
    if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
    	          cout<<"\n----------------------------------START PACKET-------------------------------------------------\n";          
        ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
        inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIP, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), destIP, INET_ADDRSTRLEN);

        if (ipHeader->ip_p == IPPROTO_TCP) {
        cout<<"\n********	TCP PROTOCOL PACKET	******\n";
            tcpCount = tcpCount + 1;
            tcpHeader = (struct tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
            sourcePort = ntohs(tcpHeader->source);
            destPort = ntohs(tcpHeader->dest);
            data = (u_char*)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
            dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
            
            // convert non-printable characters, other than carriage return, line feed,
          // or tab into periods when displayed.
          for (int i = 0; i < dataLength; i++) {
              if ((data[i] >= 32 && data[i] <= 126) || data[i] == 10 || data[i] == 11 || data[i] == 13) {
                  dataStr += (char)data[i];
              } else {
                  dataStr += ".";
              }
          }

          // print the results

          if (dataLength > 0) {
              cout << dataStr << endl;
          }


        } else if (ipHeader->ip_p == IPPROTO_UDP) {
        cout<<"\n********	UDP PROTOCOL PACKET	******\n";
            udpCount = udpCount + 1;
            udpHeader = (struct udphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
            sourcePort = ntohs(udpHeader->source);
            destPort = ntohs(udpHeader->dest);
            if (sourcePort == 53 || destPort == 53) {		// UDP DNS REQUEST
                dnsCount = dnsCount + 1;

            }
        } else if (ipHeader->ip_p == IPPROTO_ICMP) {
        cout<<"\n********	ICMP PROTOCOL PACKET	******\n";
            icmpCount = icmpCount + 1;
        }
    
    
    	          cout<<"\n----------------------------------HEADER-------------------------------------------------\n";
          cout <<"(SOURCE IP )"<< sourceIP << ": (SOURCE PORT )" << sourcePort << " -> (DESTINATION IP) " << destIP << ": (DESTINATION PORT) " << destPort << endl;
    	          cout<<"\n----------------------------------END PACKET-------------------------------------------------\n";          
          
    
    }

	

}



int main(int argc,char *argv[])
{
	char *dev, errbuf[PCAP_ERRBUF_SIZE];	/* dev will contain the name of interface from which we will sniff packets	
	errbuf if the buffer which will catch the error generated during execution of pcap commands
	PCAP_ERRBUF_SIZE is the max size of buff 
	*/
	pcap_t *descr;
	dev = pcap_lookupdev(errbuf);		
	int i;
	/*
	pcap_lookupdev is used to find out available network interfaces from which we can sniff 
	name is returned in dev array in case of error or no interface avail it returns null
	*/
	if(dev == NULL)
	{
		cout << "pcap_lookupdev() Failed: " << errbuf << endl;
		return 1;
	}
	cout<<"\nInterface Listening ON - "<<dev<<endl;
	
	/*
		Till here we found available interface 
		Now we will open device for sniffing
	*/
	
	/*
	pacp_open_live() is used to create packet descriptor hence enabling us to refer 
	returns descriptor on sucess and null on failure
	1. device is the name of interface used for sniffing found by lookup()
	2. snaplen is the max snap length or packet size to be handlled by this descriptor
	3. promisc determines wheather listen in promiscous mode it will analyze not
	   specifically address of your machine 
	4. to_ms reads time out in ms to read packets
	5. errbuf in case of error it contains error message
	
	*/
	
	descr = pcap_open_live(dev, BUFSIZ, 0, -1, errbuf);
  	if (descr == NULL) {
      cout << "pcap_open_live() failed: " << errbuf << endl;
      return 1;
 	}
 	cout<<"\nListening ON - "<<descr<<endl;
 	
 	
 	/*
 	pcap_loop() takes our descriptor and start sniffing packets sending them to handler
	callback function 
	1. descr it is packet descriptor
	2. count is no of packet to capture before pcaploop exists use -1 or 0 for no limit
	3. callback is the callback function which is called every time a packet is sniffed 
		is recives relavent userdata, pcap headers and full packet data 
	4. userdata is array of unsigned bytes to be sent in with each packet you can hold and 
		relevant user data you like to send with this

 	
 	*/
 	
 	if (pcap_loop(descr, 25, packetHandler, NULL) < 0) {
      cout << "pcap_loop() failed: " << pcap_geterr(descr);
      return 1;
	  }
	  

    cout<<"Protocol Summary: ICMP packets  "<<icmpCount<<" TCP packets "<<tcpCount<<" UDP packets  "<<udpCount;
    cout<<"  DNS Summary: packets "<<dnsCount;

	  cout << "capture finished" << endl;

 	
 	
	
	return 0;
}











/*




		 A summary of the contents of the internet header follows: 

           0                   1                   2                   3   
           0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |Version|  IHL  |Type of Service|          Total Length         |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |         Identification        |Flags|      Fragment Offset    |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |  Time to Live |    Protocol   |         Header Checksum       |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                       Source Address                          |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                    Destination Address                        |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          |                    Options                    |    Padding    |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          
          
          















*/
