set chan            Channel/WirelessChannel
set prop            Propagation/TwoRayGround
set netif           Phy/WirelessPhy
set rp              AODV
set ifq             Queue/DropTail/PriQueue
set ifqlen          50
set mac             Mac/802_11
set ant             Antenna/OmniAntenna
set ll              LL
set nn              3
set x               500
set y               500


set ns [new Simulator]

set tracefile [open wireless.tr w]
$ns trace-all $tracefile

set namfile [open wireless.nam w]
$ns namtrace-all-wireless $namfile $x $y

set topo [new Topography]
$topo load_flatgrid $x $y

create-god $nn

$ns node-config -adhocRouting $rp \
                -llType $ll \
                -macType $mac \
                -ifqType $ifq \
                -ifqLen $ifqlen \
                -antType $ant \
                -propType $prop \
                -phyType $netif \
                -channelType $chan \
                -topoInstance $topo \
                -agentTrace ON \
                -movementTrace ON \
                -macTrace ON \
                -routerTrace ON


for {set i 0} {$i < $nn} {incr i} {
    set node_($i) [$ns node]
}

$node_(0) set X_ 10.0
$node_(0) set Y_ 200.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 350.0
$node_(1) set Y_ 250.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 120.0
$node_(2) set Y_ 230.0
$node_(2) set Z_ 0.0

$ns at 1.0 "$node_(0) setdest 80.0 250.0 5.0"
$ns at 8.0 "$node_(1) setdest 150.0 250.0 5.0"

set udp [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $node_(0) $udp
$ns attach-agent $node_(1) $null
$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set interval_ 0.0065 
$ns at 1.0 "$cbr start"

for {set i 0} {$i < $nn} {incr i} {
    $ns initial_node_pos $node_($i) 20
}

$ns at 30.0 "finish"

proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exit 0
}

$ns run
