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
	    ObjectFactory pos;
	    pos.SetTypeId("ns3::RandomRectanglePositionAllocator");
	    pos.Set("X", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=1000.0]"));
	    pos.Set("Y", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=1000.0]"));

	    std::ostringstream speedConstantRandomVariableStream;
	    speedConstantRandomVariableStream << "ns3::ConstantRandomVariable[Constant=" << 50 << "]";

	    Ptr<PositionAllocator> taPositionAlloc = pos.Create()->GetObject<PositionAllocator>();
	    mobility.SetMobilityModel("ns3::RandomWaypointMobilityModel",
		                      "Speed",
		                      StringValue(speedConstantRandomVariableStream.str()),
		                      "Pause",
		                      StringValue("ns3::ConstantRandomVariable[Constant=2.0]"),
		                      "PositionAllocator",
		                      PointerValue(taPositionAlloc));
	    mobility.SetPositionAllocator(taPositionAlloc);
	    mobility.Install(nodes);
		
	
		
	AnimationInterface anim("Random_Waypoint.xml");
	Simulator::Stop(Seconds(100.0)); 
	Simulator::Run();
	Simulator::Destroy();
	return 0;

}
