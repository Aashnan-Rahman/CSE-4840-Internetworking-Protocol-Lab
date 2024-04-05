#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("MobilityModelExample");

int main(int argc, char *argv[]) {
	Time::SetResolution(Time::MS);
	NodeContainer nodes;	
	nodes.Create(10); // Create 10 nodes
	
	MobilityHelper mobility;
	mobility.SetPositionAllocator("ns3::GridPositionAllocator", "MinX", DoubleValue(1.0), "MinY", DoubleValue(1.0), "DeltaX",
	DoubleValue(5.0),
	"DeltaY",
	DoubleValue(5.0),
	"GridWidth",
	UintegerValue(3),
	"LayoutType",
	StringValue("RowFirst"));
	// Set up the Random Walk 2d mobility model
	mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel", "Bounds", RectangleValue(Rectangle(0, 20, 0, 20)),  "Distance", DoubleValue(10), "Speed", StringValue("ns3::ConstantRandomVariable[Constant=1.0]") ); 
	
	mobility.Install(nodes);
	
		
	AnimationInterface anim("Random_Waypoint.xml");
	Simulator::Stop(Seconds(100.0)); 
	Simulator::Run();
	Simulator::Destroy();
	return 0;

}
