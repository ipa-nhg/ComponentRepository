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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#ifndef _COMPONENTKINECTV2SERVER_HH
#define _COMPONENTKINECTV2SERVER_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ComponentKinectV2ServerCore.hh"

#include "ComponentKinectV2ServerPortFactoryInterface.hh"
#include "ComponentKinectV2ServerExtension.hh"

// forward declarations
class ComponentKinectV2ServerPortFactoryInterface;
class ComponentKinectV2ServerExtension;

// includes for ComponentKinectV2ServerROSExtension

// includes for PlainOpcUaComponentKinectV2ServerExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBaseState.hh>
#include <CommBasicObjects/CommBaseStateACE.hh>
#include <CommBasicObjects/CommDevicePoseState.hh>
#include <CommBasicObjects/CommDevicePoseStateACE.hh>
#include <DomainVision/CommRGBDImage.hh>
#include <DomainVision/CommRGBDImageACE.hh>
#include <DomainVision/CommVideoImage.hh>
#include <DomainVision/CommVideoImageACE.hh>
#include <CommBasicObjects/CommVoid.hh>
#include <CommBasicObjects/CommVoidACE.hh>

// include tasks
#include "ImageTask.hh"
// include UpcallManagers
#include "BasePushTimedClientUpcallManager.hh"
#include "PtuPosePushNewestClientUpcallManager.hh"

// include input-handler
// include input-handler
#include "ColorImageQueryHandler.hh"
#include "ImageQueryHandler.hh"

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP ComponentKinectV2Server::instance()

class ComponentKinectV2Server : public ComponentKinectV2ServerCore {
private:
	static ComponentKinectV2Server *_componentKinectV2Server;
	
	// constructor
	ComponentKinectV2Server();
	
	// copy-constructor
	ComponentKinectV2Server(const ComponentKinectV2Server& cc);
	
	// destructor
	~ComponentKinectV2Server() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, ComponentKinectV2ServerPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, ComponentKinectV2ServerExtension*> componentExtensionRegistry;
	
public:
	ParameterStateStruct getGlobalState() const
	{
		return paramHandler.getGlobalState();
	}
	
	ParameterStateStruct getParameters() const
	{
		return paramHandler.getGlobalState();
	}
	
	// define tasks
	Smart::TaskTriggerSubject* imageTaskTrigger;
	ImageTask *imageTask;
	
	// define input-ports
	// InputPort basePushTimedClient
	Smart::IPushClientPattern<CommBasicObjects::CommBaseState> *basePushTimedClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommBaseState> *basePushTimedClientInputTaskTrigger;
	BasePushTimedClientUpcallManager *basePushTimedClientUpcallManager;
	// InputPort ptuPosePushNewestClient
	Smart::IPushClientPattern<CommBasicObjects::CommDevicePoseState> *ptuPosePushNewestClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommDevicePoseState> *ptuPosePushNewestClientInputTaskTrigger;
	PtuPosePushNewestClientUpcallManager *ptuPosePushNewestClientUpcallManager;
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::IPushServerPattern<DomainVision::CommVideoImage> *colorImagePushNewestServer;
	Smart::IPushServerPattern<DomainVision::CommRGBDImage> *imagePushNewestServer;
	
	// define answer-ports
	Smart::IQueryServerPattern<CommBasicObjects::CommVoid, DomainVision::CommVideoImage,SmartACE::QueryId> *colorImageQueryServer;
	Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, DomainVision::CommVideoImage,SmartACE::QueryId> *colorImageQueryServerInputTaskTrigger;
	Smart::IQueryServerPattern<CommBasicObjects::CommVoid, DomainVision::CommRGBDImage,SmartACE::QueryId> *imageQueryV2Server;
	Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, DomainVision::CommRGBDImage,SmartACE::QueryId> *imageQueryV2ServerInputTaskTrigger;
	
	// define request-handlers
	ColorImageQueryHandler *colorImageQueryHandler;
	ImageQueryHandler *imageQueryHandler;
	
	// definitions of ComponentKinectV2ServerROSExtension
	
	// definitions of PlainOpcUaComponentKinectV2ServerExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, ComponentKinectV2ServerPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(ComponentKinectV2ServerExtension *extension);
	
	/// this method allows to access the registered component-extensions (automatically converting to the actuall implementation type)
	template <typename T>
	T* getExtension(const std::string &name) {
		auto it = componentExtensionRegistry.find(name);
		if(it != componentExtensionRegistry.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return 0;
	}
	
	/// initialize component's internal members
	void init(int argc, char *argv[]);
	
	/// execute the component's infrastructure
	void run();
	
	/// clean-up component's resources
	void fini();
	
	/// call this method to set the overall component into the Alive state (i.e. component is then ready to operate)
	void setStartupFinished();
	
	/// connect all component's client ports
	Smart::StatusCode connectAndStartAllServices();
	
	/// start all assocuated Activities
	void startAllTasks();
	
	/// start all associated timers
	void startAllTimers();
	
	Smart::StatusCode connectBasePushTimedClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectPtuPosePushNewestClient(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static ComponentKinectV2Server* instance()
	{
		if(_componentKinectV2Server == 0) {
			_componentKinectV2Server = new ComponentKinectV2Server();
		}
		return _componentKinectV2Server;
	}
	
	static void deleteInstance() {
		if(_componentKinectV2Server != 0) {
			delete _componentKinectV2Server;
		}
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialComponentMode;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		struct ImageTask_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} imageTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct ColorImagePushNewestServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} colorImagePushNewestServer;
		struct ColorImageQueryServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} colorImageQueryServer;
		struct ImagePushNewestServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} imagePushNewestServer;
		struct ImageQueryV2Server_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} imageQueryV2Server;
	
		//--- client port parameter ---
		struct BasePushTimedClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} basePushTimedClient;
		struct PtuPosePushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} ptuPosePushNewestClient;
		
		// -- parameters for ComponentKinectV2ServerROSExtension
		
		// -- parameters for PlainOpcUaComponentKinectV2ServerExtension
		
	} connections;
};
#endif
