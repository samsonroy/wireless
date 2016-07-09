#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"

using namespace ns3;

int main(int argc,char *argv[])
{
NodeContainer wifiNodes;
wifiNodes.Create(3);

YansWifiPhyHelper wifiPhy=YansWifiPhyHelper::Default();
YansWifiChannelHelper wifiChannel=YansWifiChannelHelper::Default();

wifiPhy.SetChannel(wifiChannel.Create());
WifiHelper wifi=WifiHelper::Default();

NqosWifiMacHelper wifiMac=NqosWifiMacHelper::Default();
wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager");
wifiMac.SetType("ns3::AdhocWifiMac");

NetDeviceContainer wifiDevices=wifi.Install(wifiPhy,wifiMac,wifiNodes);

MobilityHelper mobility;
mobility.SetPositionAllocator("ns3::GridPositionAllocator",
"MinX",DoubleValue(0.0),
"MinY",DoubleValue(0.0),
"DeltaX",DoubleValue(5.0),
"DeltaY",DoubleValue(10.0),
"GridWidth",UintegerValue(3),
"LayoutType",StringValue("RowFirst"));
mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
mobility.Install(wifiNodes);


Simulator::Run();
Simulator::Destroy();
return 0;
}















