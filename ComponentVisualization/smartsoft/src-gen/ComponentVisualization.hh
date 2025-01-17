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
#ifndef _COMPONENTVISUALIZATION_HH
#define _COMPONENTVISUALIZATION_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ComponentVisualizationCore.hh"

#include "ComponentVisualizationPortFactoryInterface.hh"
#include "ComponentVisualizationExtension.hh"

// forward declarations
class ComponentVisualizationPortFactoryInterface;
class ComponentVisualizationExtension;

// includes for ComponentVisualizationROSExtension

// includes for PlainOpcUaComponentVisualizationExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBaseState.hh>
#include <CommBasicObjects/CommBaseStateACE.hh>
#include <DomainVision/CommDepthImage.hh>
#include <DomainVision/CommDepthImageACE.hh>
#include <CommTrackingObjects/CommDetectedPerson.hh>
#include <CommTrackingObjects/CommDetectedPersonACE.hh>
#include <CommNavigationObjects/CommGridMap.hh>
#include <CommNavigationObjects/CommGridMapACE.hh>
#include <CommNavigationObjects/CommGridMapRequest.hh>
#include <CommNavigationObjects/CommGridMapRequestACE.hh>
#include <CommBasicObjects/CommMobileIRScan.hh>
#include <CommBasicObjects/CommMobileIRScanACE.hh>
#include <CommBasicObjects/CommMobileLaserScan.hh>
#include <CommBasicObjects/CommMobileLaserScanACE.hh>
#include <CommBasicObjects/CommMobileUltrasonicScan.hh>
#include <CommBasicObjects/CommMobileUltrasonicScanACE.hh>
#include <CommTrackingObjects/CommPersonDetectionEventResult.hh>
#include <CommTrackingObjects/CommPersonDetectionEventResultACE.hh>
#include <CommTrackingObjects/CommPersonId.hh>
#include <CommTrackingObjects/CommPersonIdACE.hh>
#include <CommTrackingObjects/CommPersonLostEventParameter.hh>
#include <CommTrackingObjects/CommPersonLostEventParameterACE.hh>
#include <DomainVision/CommRGBDImage.hh>
#include <DomainVision/CommRGBDImageACE.hh>
#include <DomainVision/CommVideoImage.hh>
#include <DomainVision/CommVideoImageACE.hh>
#include <CommBasicObjects/CommVoid.hh>
#include <CommBasicObjects/CommVoidACE.hh>
#include <CommTrackingObjects/PersonLostEventState.hh>
#include <CommTrackingObjects/PersonLostEventStateACE.hh>

// include tasks
#include "BaseTask.hh"
#include "CurMapTask.hh"
#include "DepthTask.hh"
#include "IRTask.hh"
#include "ImageTask.hh"
#include "Laser1Task.hh"
#include "Laser2Task.hh"
#include "Laser3Task.hh"
#include "ManagementTask.hh"
#include "PersonDetectionTask.hh"
#include "RGBDTask.hh"
#include "USArTask.hh"
// include UpcallManagers
#include "BaseClientUpcallManager.hh"
#include "CurPushClientUpcallManager.hh"
#include "DepthPushNewestClientUpcallManager.hh"
#include "ImagePushNewestClientUpcallManager.hh"
#include "IrPushNewestClientUpcallManager.hh"
#include "LaserClient1UpcallManager.hh"
#include "LaserClient2UpcallManager.hh"
#include "LaserClient3UpcallManager.hh"
#include "PersonDetectionEventClientUpcallManager.hh"
#include "RgbdPushNewestClientUpcallManager.hh"
#include "RgbdQueryClientUpcallManager.hh"
#include "UltrasonicPushNewestClientUpcallManager.hh"

// include input-handler
// include input-handler

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP ComponentVisualization::instance()

class ComponentVisualization : public ComponentVisualizationCore {
private:
	static ComponentVisualization *_componentVisualization;
	
	// constructor
	ComponentVisualization();
	
	// copy-constructor
	ComponentVisualization(const ComponentVisualization& cc);
	
	// destructor
	~ComponentVisualization() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, ComponentVisualizationPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, ComponentVisualizationExtension*> componentExtensionRegistry;
	
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
	Smart::TaskTriggerSubject* baseTaskTrigger;
	BaseTask *baseTask;
	Smart::TaskTriggerSubject* curMapTaskTrigger;
	CurMapTask *curMapTask;
	Smart::TaskTriggerSubject* depthTaskTrigger;
	DepthTask *depthTask;
	Smart::TaskTriggerSubject* iRTaskTrigger;
	IRTask *iRTask;
	Smart::TaskTriggerSubject* imageTaskTrigger;
	ImageTask *imageTask;
	Smart::TaskTriggerSubject* laser1TaskTrigger;
	Laser1Task *laser1Task;
	Smart::TaskTriggerSubject* laser2TaskTrigger;
	Laser2Task *laser2Task;
	Smart::TaskTriggerSubject* laser3TaskTrigger;
	Laser3Task *laser3Task;
	Smart::TaskTriggerSubject* managementTaskTrigger;
	ManagementTask *managementTask;
	Smart::TaskTriggerSubject* personDetectionTaskTrigger;
	PersonDetectionTask *personDetectionTask;
	Smart::TaskTriggerSubject* rGBDTaskTrigger;
	RGBDTask *rGBDTask;
	Smart::TaskTriggerSubject* uSArTaskTrigger;
	USArTask *uSArTask;
	
	// define input-ports
	// InputPort baseClient
	Smart::IPushClientPattern<CommBasicObjects::CommBaseState> *baseClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommBaseState> *baseClientInputTaskTrigger;
	BaseClientUpcallManager *baseClientUpcallManager;
	// InputPort curPushClient
	Smart::IPushClientPattern<CommNavigationObjects::CommGridMap> *curPushClient;
	Smart::InputTaskTrigger<CommNavigationObjects::CommGridMap> *curPushClientInputTaskTrigger;
	CurPushClientUpcallManager *curPushClientUpcallManager;
	// InputPort depthPushNewestClient
	Smart::IPushClientPattern<DomainVision::CommDepthImage> *depthPushNewestClient;
	Smart::InputTaskTrigger<DomainVision::CommDepthImage> *depthPushNewestClientInputTaskTrigger;
	DepthPushNewestClientUpcallManager *depthPushNewestClientUpcallManager;
	// InputPort imagePushNewestClient
	Smart::IPushClientPattern<DomainVision::CommVideoImage> *imagePushNewestClient;
	Smart::InputTaskTrigger<DomainVision::CommVideoImage> *imagePushNewestClientInputTaskTrigger;
	ImagePushNewestClientUpcallManager *imagePushNewestClientUpcallManager;
	// InputPort irPushNewestClient
	Smart::IPushClientPattern<CommBasicObjects::CommMobileIRScan> *irPushNewestClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileIRScan> *irPushNewestClientInputTaskTrigger;
	IrPushNewestClientUpcallManager *irPushNewestClientUpcallManager;
	// InputPort laserClient1
	Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> *laserClient1;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan> *laserClient1InputTaskTrigger;
	LaserClient1UpcallManager *laserClient1UpcallManager;
	// InputPort laserClient2
	Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> *laserClient2;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan> *laserClient2InputTaskTrigger;
	LaserClient2UpcallManager *laserClient2UpcallManager;
	// InputPort laserClient3
	Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> *laserClient3;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan> *laserClient3InputTaskTrigger;
	LaserClient3UpcallManager *laserClient3UpcallManager;
	// InputPort personDetectionEventClient
	Smart::IEventClientPattern<CommTrackingObjects::CommPersonLostEventParameter, CommTrackingObjects::CommPersonDetectionEventResult,SmartACE::EventId> *personDetectionEventClient;
	Smart::InputTaskTrigger<Smart::EventInputType<CommTrackingObjects::CommPersonDetectionEventResult,SmartACE::EventId>> *personDetectionEventClientInputTaskTrigger;
	PersonDetectionEventClientUpcallManager *personDetectionEventClientUpcallManager;
	// InputPort rgbdPushNewestClient
	Smart::IPushClientPattern<DomainVision::CommRGBDImage> *rgbdPushNewestClient;
	Smart::InputTaskTrigger<DomainVision::CommRGBDImage> *rgbdPushNewestClientInputTaskTrigger;
	RgbdPushNewestClientUpcallManager *rgbdPushNewestClientUpcallManager;
	// InputPort rgbdQueryClient
	Smart::IPushClientPattern<DomainVision::CommDepthImage> *rgbdQueryClient;
	Smart::InputTaskTrigger<DomainVision::CommDepthImage> *rgbdQueryClientInputTaskTrigger;
	RgbdQueryClientUpcallManager *rgbdQueryClientUpcallManager;
	// InputPort ultrasonicPushNewestClient
	Smart::IPushClientPattern<CommBasicObjects::CommMobileUltrasonicScan> *ultrasonicPushNewestClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileUltrasonicScan> *ultrasonicPushNewestClientInputTaskTrigger;
	UltrasonicPushNewestClientUpcallManager *ultrasonicPushNewestClientUpcallManager;
	
	// define request-ports
	Smart::IQueryClientPattern<CommBasicObjects::CommVoid, DomainVision::CommRGBDImage,SmartACE::QueryId> *rGBDImageQueryServiceReq;
	Smart::IQueryClientPattern<CommNavigationObjects::CommGridMapRequest, CommNavigationObjects::CommGridMap,SmartACE::QueryId> *ltmQueryClient;
	Smart::IQueryClientPattern<CommTrackingObjects::CommPersonId, CommTrackingObjects::CommDetectedPerson,SmartACE::QueryId> *personDetectionQueryClient;
	
	// define input-handler
	
	// define output-ports
	
	// define answer-ports
	
	// define request-handlers
	
	// definitions of ComponentVisualizationROSExtension
	
	// definitions of PlainOpcUaComponentVisualizationExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, ComponentVisualizationPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(ComponentVisualizationExtension *extension);
	
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
	
	Smart::StatusCode connectRGBDImageQueryServiceReq(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectBaseClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectCurPushClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectDepthPushNewestClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectImagePushNewestClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectIrPushNewestClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectLaserClient1(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectLaserClient2(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectLaserClient3(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectLtmQueryClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectPersonDetectionEventClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectPersonDetectionQueryClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectRgbdPushNewestClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectRgbdQueryClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectUltrasonicPushNewestClient(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static ComponentVisualization* instance()
	{
		if(_componentVisualization == 0) {
			_componentVisualization = new ComponentVisualization();
		}
		return _componentVisualization;
	}
	
	static void deleteInstance() {
		if(_componentVisualization != 0) {
			delete _componentVisualization;
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
		struct BaseTask_struct {
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
		} baseTask;
		struct CurMapTask_struct {
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
		} curMapTask;
		struct DepthTask_struct {
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
		} depthTask;
		struct IRTask_struct {
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
		} iRTask;
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
		struct Laser1Task_struct {
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
		} laser1Task;
		struct Laser2Task_struct {
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
		} laser2Task;
		struct Laser3Task_struct {
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
		} laser3Task;
		struct ManagementTask_struct {
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
		} managementTask;
		struct PersonDetectionTask_struct {
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
		} personDetectionTask;
		struct RGBDTask_struct {
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
		} rGBDTask;
		struct USArTask_struct {
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
		} uSArTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
	
		//--- client port parameter ---
		struct RGBDImageQueryServiceReq_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} rGBDImageQueryServiceReq;
		struct BaseClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} baseClient;
		struct CurPushClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} curPushClient;
		struct DepthPushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} depthPushNewestClient;
		struct ImagePushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} imagePushNewestClient;
		struct IrPushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} irPushNewestClient;
		struct LaserClient1_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} laserClient1;
		struct LaserClient2_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} laserClient2;
		struct LaserClient3_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} laserClient3;
		struct LtmQueryClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} ltmQueryClient;
		struct PersonDetectionEventClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} personDetectionEventClient;
		struct PersonDetectionQueryClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} personDetectionQueryClient;
		struct RgbdPushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} rgbdPushNewestClient;
		struct RgbdQueryClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} rgbdQueryClient;
		struct UltrasonicPushNewestClient_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} ultrasonicPushNewestClient;
		
		// -- parameters for ComponentVisualizationROSExtension
		
		// -- parameters for PlainOpcUaComponentVisualizationExtension
		
	} connections;
};
#endif
