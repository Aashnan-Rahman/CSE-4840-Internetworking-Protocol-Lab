// Aashnan Rahman
// ID 190041204
// CSE 4840 Lab 0 Task 2

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

/*
// Ring topology with 4 nodes
//
//        n0 ---- n1
//        |	  |
//        |	  |
//        n3 ---- n2
//
*/

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FirstScriptExample");

int
main(int argc, char* argv[])
{
    CommandLine cmd(__FILE__);
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    // Creating Nodes
    NodeContainer nodes;
    nodes.Create(4);

    // Create point-to-point links
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    // Install internet stack on nodes
    InternetStackHelper stack;
    stack.Install(nodes);

    // Assign IP addresses to nodes
    Ipv4AddressHelper address;
    address.SetBase("192.4.4.0", "255.255.255.0");



    NetDeviceContainer devices;

    uint32_t edges[4][2] = { {0, 1}, {1, 2}, {2, 3},  {3, 0} };

    for (uint32_t i = 0; i <= 3; ++i)
    {
    	devices.Add(pointToPoint.Install(nodes.Get(i), nodes.Get((i+1)%4)));
    }

    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    //Server will listen on port 9
    UdpEchoServerHelper echoServer(9);


    for (uint32_t i = 0; i <= 3; ++i)
    {

    	uint32_t server = edges[i][0], client = edges[i][1];

    	ApplicationContainer serverApps = echoServer.Install(nodes.Get(server));
    	serverApps.Start(Seconds(1.0 + 10.0*i));
    	serverApps.Stop(Seconds(10.0 + 10.0*i));


	UdpEchoClientHelper echoClient(interfaces.GetAddress(server), 9);
	echoClient.SetAttribute("MaxPackets", UintegerValue(1));
	echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize", UintegerValue(1024));

	ApplicationContainer clientApps = echoClient.Install(nodes.Get(client));
	clientApps.Start(Seconds(2.0 + 10.0*i));
	clientApps.Stop(Seconds(10.0 + 10.0*i));


    }


    // Run simulation
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}

