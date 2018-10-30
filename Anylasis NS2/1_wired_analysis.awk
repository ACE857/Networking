
BEGIN {

    seqno = -1;    

    droppedPackets = 0; 

    receivedPackets = 0;
    
    tcps = 0;

    tcpr = 0;
    
    tcpd = 0;

    udps = 0;

    udpr = 0;

    udpd = 0;

    acks = 0;

    ackr = 0;

    ackd = 0; 

    count = 0;

}

{

#packet delivery ratio for all packets


#For couting total no of send (tcp,udp and ack)
    	
    if (($1 == "+") && (seqno < $12))
    	{
	seqno = $12;
    	}


#For couting total no of receive at destination node4 and node5 (tcp,udp and ack)
 
    
else if(($1 == "r") && (($5 == "cbr") || ($5 == "tcp") || ($5 == "ack"))&& (($4 == "4") || ($4 == "5") || ($4 == "0"))) 
	
	{
 		receivedPackets++;
	}

#For couting total no of drops
 
   else if (($1 == "d") && (($5 == "cbr") || ($5 == "tcp") || ($5 == "ack")))
	{
            droppedPackets++;            
  	}

#For individual send, receive and ack
   if (($1 == "+") && ($5 == "cbr") && ($3 == "1"))
        {
		udps++;
	}
   else if (($1 == "+") && ($5 == "tcp") && ($3 == "0"))
        {
		tcps++;
	}
   else if (($1 == "+") && ($5 == "ack") && ($3 == "4"))
	{
		acks++;
	}
   else if (($1 == "r") && ($5 == "cbr") && ($4 == "5"))
	{
		udpr++;
	}
   else if (($1 == "r") && ($5 == "tcp") && ($4 == "4"))
        {
		tcpr++;
	}
   else if (($1 == "r") && ($5 == "ack") && ($4 == "0"))
	{
		ackr++;
	}
   else if (($1 == "d") && ($5 == "cbr"))
	{
		udpd++;
	}
   else if (($1 == "d") && ($5 == "tcp"))
	{
		tcpd++;
	}
   else if (($1 == "d") && ($5 == "ack"))
	{
		ackd++;
	}
    #end-to-end delay
   if (($1 == "+") && (seqno < $12))
	{
	start_time[$12] = $2;
	}   
   else if(($1 == "r") && ($5 == "cbr"))
	{
	end_time[$12] = $2;
	}
  else if(($1 == "d") && ($5 == "cbr"))
        {
        end_time[$6] = -1;
	} 
}

 
END {        

  

    for(i=0; i<=seqno; i++) {

          if(end_time[i] > 0) {

              delay[i] = end_time[i] - start_time[i];

                  count++;

        }

            else

            {

                  delay[i] = -1;

            }

    }

    for(i=0; i<count; i++) {

          if(delay[i] > 0) {

              n_to_n_delay = n_to_n_delay + delay[i];

        }         

    }

   n_to_n_delay = n_to_n_delay/count;

 

    print "\n";

    print "Total no of GeneratedPackets            = " seqno+1;

    print "Total no of ReceivedPackets             = " receivedPackets;

    print "Total no of Dropped Packets = " droppedPackets;

    print "Total Packet Delivery Ratio      = " receivedPackets/(seqno+1)*100
"%";
    print "Total no of TCP send            = " tcps;

    print "Total no of UDP send            = " udps;

    print "Total no of ACK send            = " acks;
    
    print "Total no of TCP receive            = " tcpr;

    print "Total no of UDP receive            = " udpr;

    print "Total no of ACK receive            = " ackr;
    
    print "Total no of TCP drop            = " tcpd;

    print "Total no of UDP drop            = " udpd;

    print "Total no of ACK drop            = " ackd;

    print "Average End-to-End Delay    = " n_to_n_delay" s";

    print "\n";

} 
