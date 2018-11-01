BEGIN {

    start_time = 1e6
    stop_time = 0

    sentPkt = 0
    recdPkt = 0
    forwardPkt = 0
}

{
    event = $1
    time = $2
    packet = $4

    if(packet == "AGT" && (event == "+" || event == "s")) {
        if(start_time > time) {
            start_time = time
        }
        ++sentPkt;
    }

    if(packet == "AGT" && event == "r") {
        if(stop_time < time) {
            stop_time = time
        }
        ++recdPkt;
    }
    
    if(packet == "RTR" && event == "f") {
        ++forwardPkt;
    }
}

END {

    if(recdPkt == 0) {
        printf("\n\n\nNo packets received!!!!\n\n\n")
    }

    printf("\nStart Time: %d", start_time)
    printf("\nStop Time: %d", stop_time)

    printf("\nPackets sent: %d", sentPkt)
    printf("\nPackets received: %d", recdPkt)
    printf("\nPackets forwarded: %d", forwardPkt)

    printf("\nThroughput (k-bits/sec): %f", (recdPkt/(stop_time-start_time)*(8/1000)))
    printf("\nDelivery ratio (k-bits/sec): %f", (recdPkt/sentPkt))
    printf("\n")

}
