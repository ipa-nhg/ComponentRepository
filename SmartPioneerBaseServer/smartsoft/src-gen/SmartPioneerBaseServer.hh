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
#ifndef _SMARTPIONEERBASESERVER_HH
#define _SMARTPIONEERBASESERVER_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "SmartPioneerBaseServerCore.hh"

#include "SmartPioneerBaseServerPortFactoryInterface.hh"
#include "SmartPioneerBaseServerExtension.hh"

// forward declarations
class SmartPioneerBaseServerPortFactoryInterface;
class SmartPioneerBaseServerExtension;

// includes for SmartPioneerBaseServerROSExtension

// includes for PlainOpcUaSmartPioneerBaseServerExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBasePositionUpdate.hh>
#include <CommBasicObjects/CommBasePositionUpdateACE.hh>
#include <CommBasicObjects/CommBaseState.hh>
#include <CommBasicObjects/CommBaseStateACE.hh>
#include <CommBasicObjects/CommBatteryEvent.hh>
#include <CommBasicObjects/CommBatteryEventACE.hh>
#include <CommBasicObjects/CommBatteryParameter.hh>
#include <CommBasicObjects/CommBatteryParameterACE.hh>
#include <CommBasicObjects/CommBatteryState.hh>
#include <CommBasicObjects/CommBatteryStateACE.hh>
#include <CommBasicObjects/CommNavigationVelocity.hh>
#include <CommBasicObjects/CommNavigationVelocityACE.hh>
#include <CommBasicObjects/CommVoid.hh>
#include <CommBasicObjects/CommVoidACE.hh>

// include tasks
#include "PoseUpdateTask.hh"
#include "RobotTask.hh"
// include UpcallManagers
#include "LocalizationUpdateUpcallManager.hh"
#include "NavVelInUpcallManager.hh"

// include input-handler
// include input-handler
#include "BaseStateQueryHandler.hh"

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP SmartPioneerBaseServer::instance()

class SmartPioneerBaseServer : public SmartPioneerBaseServerCore {
private:
	static SmartPioneerBaseServer *_smartPioneerBaseServer;
	
	// constructor
	SmartPioneerBaseServer();
	
	// copy-constructor
	SmartPioneerBaseServer(const SmartPioneerBaseServer& cc);
	
	// destructor
	~SmartPioneerBaseServer() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, SmartPioneerBaseServerPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, SmartPioneerBaseServerExtension*> componentExtensionRegistry;
	
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
	Smart::TaskTriggerSubject* poseUpdateTaskTrigger;
	PoseUpdateTask *poseUpdateTask;
	Smart::TaskTriggerSubject* robotTaskTrigger;
	RobotTask *robotTask;
	
	// define input-ports
	// InputPort LocalizationUpdate
	Smart::ISendServerPattern<CommBasicObjects::CommBasePositionUpdate> *localizationUpdate;
	Smart::InputTaskTrigger<CommBasicObjects::CommBasePositionUpdate> *localizationUpdateInputTaskTrigger;
	LocalizationUpdateUpcallManager *localizationUpdateUpcallManager;
	// InputPort NavVelIn
	Smart::ISendServerPattern<CommBasicObjects::CommNavigationVelocity> *navVelIn;
	Smart::InputTaskTrigger<CommBasicObjects::CommNavigationVelocity> *navVelInInputTaskTrigger;
	NavVelInUpcallManager *navVelInUpcallManager;
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::IPushServerPattern<CommBasicObjects::CommBaseState> *basePositionOut;
	Smart::IEventServerPattern<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState,SmartACE::EventId> *batteryEventServer;
	Smart::IEventTestHandler<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState> *batteryEventServerEventTestHandler; 
	
	// define answer-ports
	Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> *baseStateQueryServer;
	Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> *baseStateQueryServerInputTaskTrigger;
	
	// define request-handlers
	BaseStateQueryHandler *baseStateQueryHandler;
	
	// definitions of SmartPioneerBaseServerROSExtension
	
	// definitions of PlainOpcUaSmartPioneerBaseServerExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, SmartPioneerBaseServerPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(SmartPioneerBaseServerExtension *extension);
	
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
	

	// return singleton instance
	static SmartPioneerBaseServer* instance()
	{
		if(_smartPioneerBaseServer == 0) {
			_smartPioneerBaseServer = new SmartPioneerBaseServer();
		}
		return _smartPioneerBaseServer;
	}
	
	static void deleteInstance() {
		if(_smartPioneerBaseServer != 0) {
			delete _smartPioneerBaseServer;
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
		struct PoseUpdateTask_struct {
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
		} poseUpdateTask;
		struct RobotTask_struct {
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} robotTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct BasePositionOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} basePositionOut;
		struct BaseStateQueryServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} baseStateQueryServer;
		struct BatteryEventServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} batteryEventServer;
		struct LocalizationUpdate_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} localizationUpdate;
		struct NavVelIn_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} navVelIn;
	
		//--- client port parameter ---
		
		// -- parameters for SmartPioneerBaseServerROSExtension
		
		// -- parameters for PlainOpcUaSmartPioneerBaseServerExtension
		
	} connections;
};
#endif
