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
#ifndef _COMPONENTUNICAPIMAGECLIENT_HH
#define _COMPONENTUNICAPIMAGECLIENT_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ComponentUnicapImageClientCore.hh"

#include "ComponentUnicapImageClientPortFactoryInterface.hh"
#include "ComponentUnicapImageClientExtension.hh"

// forward declarations
class ComponentUnicapImageClientPortFactoryInterface;
class ComponentUnicapImageClientExtension;

// includes for ComponentUnicapImageClientROSExtension

// includes for PlainOpcUaComponentUnicapImageClientExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <DomainVision/CommVideoImage.hh>
#include <DomainVision/CommVideoImageACE.hh>
#include <CommBasicObjects/CommVoid.hh>
#include <CommBasicObjects/CommVoidACE.hh>

// include tasks
#include "GuiTask.hh"
#include "ImageTask.hh"
// include UpcallManagers
#include "PushNewestClientUpcallManager.hh"

// include input-handler
// include input-handler

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP ComponentUnicapImageClient::instance()

class ComponentUnicapImageClient : public ComponentUnicapImageClientCore {
private:
	static ComponentUnicapImageClient *_componentUnicapImageClient;
	
	// constructor
	ComponentUnicapImageClient();
	
	// copy-constructor
	ComponentUnicapImageClient(const ComponentUnicapImageClient& cc);
	
	// destructor
	~ComponentUnicapImageClient() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, ComponentUnicapImageClientPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, ComponentUnicapImageClientExtension*> componentExtensionRegistry;
	
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
	Smart::TaskTriggerSubject* guiTaskTrigger;
	GuiTask *guiTask;
	Smart::TaskTriggerSubject* imageTaskTrigger;
	ImageTask *imageTask;
	
	// define input-ports
	// InputPort pushNewestClient
	Smart::IPushClientPattern<DomainVision::CommVideoImage> *pushNewestClient;
	Smart::InputTaskTrigger<DomainVision::CommVideoImage> *pushNewestClientInputTaskTrigger;
	PushNewestClientUpcallManager *pushNewestClientUpcallManager;
	
	// define request-ports
	Smart::IQueryClientPattern<CommBasicObjects::CommVoid, DomainVision::CommVideoImage,SmartACE::QueryId> *queryClient;
	
	// define input-handler
	
	// define output-ports
	
	// define answer-ports
	
	// define request-handlers
	
	// definitions of ComponentUnicapImageClientROSExtension
	
	// definitions of PlainOpcUaComponentUnicapImageClientExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, ComponentUnicapImageClientPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(ComponentUnicapImageClientExtension *extension);
	
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
	
	Smart::StatusCode connectPushNewestClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectQueryClient(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static ComponentUnicapImageClient* instance()
	{
		if(_componentUnicapImageClient == 0) {
			_componentUnicapImageClient = new ComponentUnicapImageClient();
		}
		return _componentUnicapImageClient;
	}
	
	static void deleteInstance() {
		if(_componentUnicapImageClient != 0) {
			delete _componentUnicapImageClient;
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
		struct GuiTask_struct {
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
		} guiTask;
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
	
		//--- client port parameter ---
		struct PushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} pushNewestClient;
		struct QueryClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} queryClient;
		
		// -- parameters for ComponentUnicapImageClientROSExtension
		
		// -- parameters for PlainOpcUaComponentUnicapImageClientExtension
		
	} connections;
};
#endif
