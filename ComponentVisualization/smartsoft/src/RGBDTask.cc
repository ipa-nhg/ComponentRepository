//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include "RGBDTask.hh"
#include "ComponentVisualization.hh"

#include <iostream>

RGBDTask::RGBDTask(SmartACE::SmartComponent *comp) 
:	RGBDTaskCore(comp)
{
	std::cout << "constructor RGBDTask\n";
}
RGBDTask::~RGBDTask() 
{
	std::cout << "destructor RGBDTask\n";
}

int RGBDTask::connectServices(){
	std::cout << "connecting to: " << COMP->connections.rgbdPushNewestClient.serverName<< "; " << COMP->connections.rgbdPushNewestClient.serviceName
			<< std::endl;
	Smart::StatusCode status = COMP->rgbdPushNewestClient->connect(COMP->connections.rgbdPushNewestClient.serverName,
			COMP->connections.rgbdPushNewestClient.serviceName);
	while (status != Smart::SMART_OK)
	{
		usleep(500000);
		status = COMP->rgbdPushNewestClient->connect(COMP->connections.rgbdPushNewestClient.serverName,
				COMP->connections.rgbdPushNewestClient.serviceName);
	}
	std::cout << "connected.\n";
	std::cout << COMP->connections.rgbdPushNewestClient.serverName << "; " << COMP->connections.rgbdPushNewestClient.serviceName << " connected.\n";
	return 0;
}
int RGBDTask::disconnectServices(){
	COMP->rgbdPushNewestClient->disconnect();
	return 0;
}


int RGBDTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further

	rgbd_viz = new RGBDVisualization(COMP->getWindow3d(), "realsense");


	COMP->rgbdPushNewestClient->subscribe();

	return (rgbd_viz !=0)?0:1;


	return 0;
}
int RGBDTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	Smart::StatusCode status = COMP->rgbdPushNewestClient->getUpdateWait(image);
		if (status == Smart::SMART_OK)
		{
			//std::cout << "[RealSenseTask] got new RealSense image\n";
			rgbd_viz->displayImage(image);
		} else
		{
			std::cout << "[RealSenseTask] error while getting new image: " << Smart::StatusCodeConversion(status) << "\n";
		}
    //std::cout << "I am waiting" <<std::endl;
	//while (std::cin.get() != '\n');
	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int RGBDTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	delete rgbd_viz;
	COMP->rgbdPushNewestClient->unsubscribe();
	return 0;
}