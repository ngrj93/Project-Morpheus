// Infinite funnel attack - A simulation of the infinite funnel attack on a bus network

#include "ns3/aodv-module.h"
#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"
#include "myapp.h"

NS_LOG_COMPONENT_DEFINE ("InfiniteFunnel");

using namespace ns3;


void
ReceivePacket(Ptr<const Packet> p, const Address & addr)
{
	std::cout << Simulator::Now ().GetSeconds () << "\t" << p->GetSize() <<"\n";
}


int main(int argc, char *argv[]){

	std::string phyMode("DsssRate1Mbps");
	NS_LOG_INFO ("Creating cluster nodes...");

	CommandLine cmd;
	cmd.Parse (argc, argv);	
	
	NodeContainer c;
	NodeContainer not_malicious;
	NodeContainer malicious;
	c.Create(4);
	not_malicious.Add(c.Get(1));
	not_malicious.Add(c.Get(2));
	not_malicious.Add(c.Get(3));
	malicious.Add(c.Get(0));

	//Physical layer description
	WifiHelper wifi;
	YansWifiPhyHelper wifiPhy=YansWifiPhyHelper::Default();
	wifiPhy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11);
	YansWifiChannelHelper wifiChannel;
	wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
	wifiChannel.AddPropagationLoss("ns3::TwoRayGroundPropagationLossModel","SystemLoss",DoubleValue(1),"HeightAboveZ",DoubleValue(1.5));

	// For range of approx. 250m
  	wifiPhy.Set ("TxPowerStart", DoubleValue(33));
	wifiPhy.Set ("TxPowerEnd", DoubleValue(33));
	wifiPhy.Set ("TxPowerLevels", UintegerValue(1));
	wifiPhy.Set ("TxGain", DoubleValue(0));
	wifiPhy.Set ("RxGain", DoubleValue(0));
	wifiPhy.Set ("EnergyDetectionThreshold", DoubleValue(-61.8));
	wifiPhy.Set ("CcaMode1Threshold", DoubleValue(-64.8));

	wifiPhy.SetChannel (wifiChannel.Create ());
  	NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  	wifiMac.SetType ("ns3::AdhocWifiMac");

  	wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue(phyMode), "ControlMode",StringValue(phyMode));

  	NetDeviceContainer devices;
  	devices = wifi.Install (wifiPhy, wifiMac, c);
	wifiPhy.EnablePcapAll (std::string ("aodv"));
	// AODV routing protocol in underlying network layer
  	AodvHelper aodv;
  	AodvHelper malicious_aodv; 
 
  	InternetStackHelper internet;
  	internet.SetRoutingHelper (aodv);
  	internet.Install (not_malicious);
  
  	malicious_aodv.Set("IsMalicious",BooleanValue(true));
  	internet.SetRoutingHelper (malicious_aodv);
  	internet.Install (malicious);

  	// Set up Addresses
  	Ipv4AddressHelper ipv4;
  	NS_LOG_INFO ("Assigning IP Addresses...");
  	ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  	Ipv4InterfaceContainer ifcont = ipv4.Assign (devices);


//----------------------------------------------------------------

	NS_LOG_INFO ("Creating Applications...");

	// UDP connection from N1 to N3

	uint16_t sinkPort = 6;
	Address sinkAddress (InetSocketAddress (ifcont.GetAddress (3), sinkPort)); // interface of n3
	PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
	ApplicationContainer sinkApps = packetSinkHelper.Install (c.Get (3)); //n3 as sink
	sinkApps.Start (Seconds (0));
	sinkApps.Stop (Seconds (100));

	Ptr<Socket> ns3UdpSocket = Socket::CreateSocket (c.Get (1), UdpSocketFactory::GetTypeId ()); //source at n1

	// Create UDP application at n1
	Ptr<MyApp> app = CreateObject<MyApp> ();
	app->Setup (ns3UdpSocket, sinkAddress, 1040, 5, DataRate ("250Kbps"));
	c.Get (1)->AddApplication (app);
	app->SetStartTime (Seconds (40));
	app->SetStopTime (Seconds (100));

	// Mobility in temporary ad hoc hpc 

	MobilityHelper mobility;
	Ptr<ListPositionAllocator> positionAlloc = CreateObject <ListPositionAllocator>();
	positionAlloc ->Add(Vector(100, 0, 0)); // node0
	positionAlloc ->Add(Vector(200, 0, 0)); // node1 
	positionAlloc ->Add(Vector(450, 0, 0)); // node2
	positionAlloc ->Add(Vector(550, 0, 0)); // node3
	mobility.SetPositionAllocator(positionAlloc);
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(c);

	 
	Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> ("infinitefunnel.routes", std::ios::out);
	  aodv.PrintRoutingTableAllAt (Seconds (45), routingStream);

	// Trace Received Packets
	Config::ConnectWithoutContext("/NodeList/*/ApplicationList/*/$ns3::PacketSink/Rx", MakeCallback (&ReceivePacket));

	// Calculate Throughput using Flowmonitor

	FlowMonitorHelper flowmon;
	Ptr<FlowMonitor> monitor = flowmon.InstallAll();

	// Now do the actual simulation.

	NS_LOG_INFO ("Running Simulation...");
	Simulator::Stop (Seconds(100.0));
	Simulator::Run ();

	monitor->CheckForLostPackets ();

	Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
	std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
	for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
	{
		  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
		  if ((t.sourceAddress=="10.1.2.2" && t.destinationAddress == "10.1.2.4"))
		  {
			  std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
			  std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
			  std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
		  	  std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
		  }
	 }

	monitor->SerializeToXmlFile("inf.flowmon", true, true);

}
