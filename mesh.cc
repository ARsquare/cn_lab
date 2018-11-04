Conversations
4.08 GB (27%) of 15 GB used
Manage
Terms · Privacy · Program Policies
Last account activity: 0 minutes ago
Currently being used in 2 other locations · Details

#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("my_mesh");
int main (int argc, char *argv[])
{
  //Time::SetResolution (Time::NS);
  //double lat = 2.0;
  //uint64_t rate = 5000000; // Data rate in bps
  double interval = 0.05;
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer n;
  n.Create (5);
  
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  p2p.SetDeviceAttribute ("Mtu", UintegerValue (1400));
  
  NetDeviceContainer dev = p2p.Install (n.Get(0), n.Get(1));
  NetDeviceContainer dev2 = p2p.Install (n.Get(1), n.Get(2));
  NetDeviceContainer dev3 = p2p.Install (n.Get(1), n.Get(4));
  NetDeviceContainer dev4 = p2p.Install (n.Get(2), n.Get(3));
  NetDeviceContainer dev5 = p2p.Install (n.Get(3), n.Get(4));
  NetDeviceContainer dev6 = p2p.Install (n.Get(0), n.Get(3));


   
  InternetStackHelper internet;
  internet.Install (n);
  Ipv4AddressHelper ipv4;

	std::cout<<"Assign Ip Addressess\n";
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (dev);

  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i2 = ipv4.Assign (dev2);
  
  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i3 = ipv4.Assign (dev3);

  ipv4.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i4 = ipv4.Assign (dev4);

  ipv4.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer i5 = ipv4.Assign (dev5);

  ipv4.SetBase ("10.1.6.0", "255.255.255.0");
  Ipv4InterfaceContainer i6 = ipv4.Assign (dev6);
  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  uint16_t port1 = 8000; // Need different port numbers to ensure there is no conflict
  uint16_t port2 = 8001;
  uint16_t port3 = 8002;
  UdpServerHelper server1 (port1);
  UdpServerHelper server2 (port2);
  UdpServerHelper server3 (port3);
  
  ApplicationContainer apps;
  apps = server1.Install (n.Get (2));
  apps = server2.Install (n.Get (2));
  apps = server3.Install (n.Get (4));

  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  


  uint32_t MaxPacketSize = 1024;
  Time interPacketInterval = Seconds (interval);
  uint32_t maxPacketCount = 320;
  UdpClientHelper client1 (i2.GetAddress (1), port1);
  UdpClientHelper client2 (i2.GetAddress (1), port2);
  UdpClientHelper client3 (i4.GetAddress (1), port3);

  client1.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client1.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client1.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  client2.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client2.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client2.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  client3.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client3.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client3.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));

  apps = client1.Install (n.Get (0));
  apps = client2.Install (n.Get (0));
  apps = client3.Install (n.Get (3));

  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));



  std::cout<<"Run Simulation\n";
  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop (Seconds(11.0));
  
  std::cout<<"Create Xml File\n";
  AnimationInterface anim ("mymesh.xml");
  
  anim.SetConstantPosition(n.Get(0),200,200);
  anim.SetConstantPosition(n.Get(1),150,200);
  anim.SetConstantPosition(n.Get(2),100,200); 
  anim.SetConstantPosition(n.Get(3),150,100);
  anim.SetConstantPosition(n.Get(4),150,300);


  Simulator::Run ();

   return 0;
}


