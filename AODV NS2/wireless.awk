BEGIN {

    seqno = -1;    
    count = 0;
	recvdSize = 0
	startTime = 400
	stopTime = 0
}

{
	event = $1
	time = $2
	node_id = $3
	pkt_size = $8
	level = $4
	
	if (level == "AGT" && event == "s" && pkt_size >= 512) {
		if (time < startTime) {
			startTime = time
		}
	}
	
	arrival time
	if (level == "AGT" && event == "r" && pkt_size >= 512) {
		if (time > stopTime) {
			stopTime = time
		}

	hdr_size = pkt_size % 512
	pkt_size -= hdr_size
	
	recvdSize += pkt_size
	}


    if($4 == "AGT" && $1 == "s" && seqno < $6) {
          seqno = $6;

    } 
    
    
    if($4 == "AGT" && $1 == "s") {
          start_time[$6] = $2;

    } else if(($7 == "tcp") && ($1 == "r")) {
        end_time[$6] = $2;

    } else if($1 == "D" && $7 == "tcp") {
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

    for(i=0; i<=seqno; i++) {
          if(delay[i] > 0) {
              n_to_n_delay = n_to_n_delay + delay[i];
        }         
    }

   n_to_n_delay = n_to_n_delay/count;

 	printf("\nAverage Throughput[kbps] = %.2f \t\tStartTime=%.2f\tStopTime=%.2f\n\n\n",
	(recvdSize/(stopTime-startTime))*(8/1000),startTime,stopTime)

    print "\n";
    print "GeneratedPackets            = " seqno+1;
    print "ReceivedPackets             = " receivedPackets;
    print "Packet Delivery Ratio      = " receivedPackets/(seqno+1)*100"%";
    print "Total Dropped Packets = " droppedPackets;
    print "Average End-to-End Delay    = " n_to_n_delay * 1000 " ms";
    print "\n";

} 
