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
#include "ComponentGMapping.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "ComponentGMappingAcePortFactory.hh"


// initialize static singleton pointer to zero
ComponentGMapping* ComponentGMapping::_componentGMapping = 0;

// constructor
ComponentGMapping::ComponentGMapping()
{
	std::cout << "constructor of ComponentGMapping\n";
	
	// set all pointer members to NULL
	gMappingTask = NULL;
	gMappingTaskTrigger = NULL;
	basePositionUpdateClient = NULL;
	laserClient = NULL;
	laserClientInputTaskTrigger = NULL;
	laserClientUpcallManager = NULL;
	newestMapPushServer = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	
	// set default ini parameter values
	connections.component.name = "ComponentGMapping";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.newestMapPushServer.serviceName = "newestMapPushServer";
	connections.newestMapPushServer.roboticMiddleware = "ACE_SmartSoft";
	connections.basePositionUpdateClient.initialConnect = false;
	connections.basePositionUpdateClient.wiringName = "basePositionUpdateClient";
	connections.basePositionUpdateClient.serverName = "unknown";
	connections.basePositionUpdateClient.serviceName = "unknown";
	connections.basePositionUpdateClient.interval = 1;
	connections.basePositionUpdateClient.roboticMiddleware = "ACE_SmartSoft";
	connections.laserClient.initialConnect = false;
	connections.laserClient.wiringName = "laserClient";
	connections.laserClient.serverName = "unknown";
	connections.laserClient.serviceName = "unknown";
	connections.laserClient.interval = 1;
	connections.laserClient.roboticMiddleware = "ACE_SmartSoft";
	connections.gMappingTask.minActFreq = 0.0;
	connections.gMappingTask.maxActFreq = 0.0;
	// scheduling default parameters
	connections.gMappingTask.scheduler = "DEFAULT";
	connections.gMappingTask.priority = -1;
	connections.gMappingTask.cpuAffinity = -1;
	
	// initialize members of ComponentGMappingROSExtension
	
	// initialize members of PlainOpcUaComponentGMappingExtension
	
}

void ComponentGMapping::addPortFactory(const std::string &name, ComponentGMappingPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void ComponentGMapping::addExtension(ComponentGMappingExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* ComponentGMapping::getComponentImpl()
{
	return dynamic_cast<ComponentGMappingAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void ComponentGMapping::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode ComponentGMapping::connectBasePositionUpdateClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.basePositionUpdateClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = basePositionUpdateClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->basePositionUpdateClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}
Smart::StatusCode ComponentGMapping::connectLaserClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.laserClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = laserClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->laserClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	laserClient->subscribe(connections.laserClient.interval);
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode ComponentGMapping::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectBasePositionUpdateClient(connections.basePositionUpdateClient.serverName, connections.basePositionUpdateClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectLaserClient(connections.laserClient.serverName, connections.laserClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void ComponentGMapping::startAllTasks() {
	// start task GMappingTask
	if(connections.gMappingTask.scheduler != "DEFAULT") {
		ACE_Sched_Params gMappingTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.gMappingTask.scheduler == "FIFO") {
			gMappingTask_SchedParams.policy(ACE_SCHED_FIFO);
			gMappingTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.gMappingTask.scheduler == "RR") {
			gMappingTask_SchedParams.policy(ACE_SCHED_RR);
			gMappingTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		gMappingTask->start(gMappingTask_SchedParams, connections.gMappingTask.cpuAffinity);
	} else {
		gMappingTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void ComponentGMapping::startAllTimers() {
}


Smart::TaskTriggerSubject* ComponentGMapping::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "laserClient") return laserClientInputTaskTrigger;
	
	return NULL;
}


void ComponentGMapping::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		
		// initializations of ComponentGMappingROSExtension
		
		// initializations of PlainOpcUaComponentGMappingExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		ComponentGMappingPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<ComponentGMappingAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition ComponentGMapping is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		newestMapPushServer = portFactoryRegistry[connections.newestMapPushServer.roboticMiddleware]->createNewestMapPushServer(connections.newestMapPushServer.serviceName);
		
		// create client ports
		basePositionUpdateClient = portFactoryRegistry[connections.basePositionUpdateClient.roboticMiddleware]->createBasePositionUpdateClient();
		laserClient = portFactoryRegistry[connections.laserClient.roboticMiddleware]->createLaserClient();
		
		// create InputTaskTriggers and UpcallManagers
		laserClientInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan>(laserClient);
		laserClientUpcallManager = new LaserClientUpcallManager(laserClient);
		
		// create input-handler
		
		// create request-handlers
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		if(connections.basePositionUpdateClient.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::SendClient<CommBasicObjects::CommBasePositionUpdate>*>(basePositionUpdateClient)->add(wiringSlave, connections.basePositionUpdateClient.wiringName);
		}
		if(connections.laserClient.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommMobileLaserScan>*>(laserClient)->add(wiringSlave, connections.laserClient.wiringName);
		}
		
		
		
		// create Task GMappingTask
		gMappingTask = new GMappingTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.gMappingTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.gMappingTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(gMappingTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				gMappingTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task GMappingTask" << std::endl;
			}
		} else if(connections.gMappingTask.trigger == "DataTriggered") {
			gMappingTaskTrigger = getInputTaskTriggerFromString(connections.gMappingTask.inPortRef);
			if(gMappingTaskTrigger != NULL) {
				gMappingTaskTrigger->attach(gMappingTask, connections.gMappingTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.gMappingTask.inPortRef << " as activation source for Task GMappingTask" << std::endl;
			}
		} 
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void ComponentGMapping::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void ComponentGMapping::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(gMappingTaskTrigger != NULL){
		gMappingTaskTrigger->detach(gMappingTask);
		delete gMappingTask;
	}

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete laserClientInputTaskTrigger;
	delete laserClientUpcallManager;

	// destroy client ports
	delete basePositionUpdateClient;
	delete laserClient;

	// destroy server ports
	delete newestMapPushServer;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of ComponentGMappingROSExtension
	
	// destruction of PlainOpcUaComponentGMappingExtension
	
}

void ComponentGMapping::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("ComponentGMapping.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load ComponentGMapping.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: ComponentGMapping.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		// load parameters for client basePositionUpdateClient
		parameter.getBoolean("basePositionUpdateClient", "initialConnect", connections.basePositionUpdateClient.initialConnect);
		parameter.getString("basePositionUpdateClient", "serviceName", connections.basePositionUpdateClient.serviceName);
		parameter.getString("basePositionUpdateClient", "serverName", connections.basePositionUpdateClient.serverName);
		parameter.getString("basePositionUpdateClient", "wiringName", connections.basePositionUpdateClient.wiringName);
		if(parameter.checkIfParameterExists("basePositionUpdateClient", "roboticMiddleware")) {
			parameter.getString("basePositionUpdateClient", "roboticMiddleware", connections.basePositionUpdateClient.roboticMiddleware);
		}
		// load parameters for client laserClient
		parameter.getBoolean("laserClient", "initialConnect", connections.laserClient.initialConnect);
		parameter.getString("laserClient", "serviceName", connections.laserClient.serviceName);
		parameter.getString("laserClient", "serverName", connections.laserClient.serverName);
		parameter.getString("laserClient", "wiringName", connections.laserClient.wiringName);
		parameter.getInteger("laserClient", "interval", connections.laserClient.interval);
		if(parameter.checkIfParameterExists("laserClient", "roboticMiddleware")) {
			parameter.getString("laserClient", "roboticMiddleware", connections.laserClient.roboticMiddleware);
		}
		
		// load parameters for server newestMapPushServer
		parameter.getString("newestMapPushServer", "serviceName", connections.newestMapPushServer.serviceName);
		if(parameter.checkIfParameterExists("newestMapPushServer", "roboticMiddleware")) {
			parameter.getString("newestMapPushServer", "roboticMiddleware", connections.newestMapPushServer.roboticMiddleware);
		}
		
		// load parameters for task GMappingTask
		parameter.getDouble("GMappingTask", "minActFreqHz", connections.gMappingTask.minActFreq);
		parameter.getDouble("GMappingTask", "maxActFreqHz", connections.gMappingTask.maxActFreq);
		parameter.getString("GMappingTask", "triggerType", connections.gMappingTask.trigger);
		if(connections.gMappingTask.trigger == "PeriodicTimer") {
			parameter.getDouble("GMappingTask", "periodicActFreqHz", connections.gMappingTask.periodicActFreq);
		} else if(connections.gMappingTask.trigger == "DataTriggered") {
			parameter.getString("GMappingTask", "inPortRef", connections.gMappingTask.inPortRef);
			parameter.getInteger("GMappingTask", "prescale", connections.gMappingTask.prescale);
		}
		if(parameter.checkIfParameterExists("GMappingTask", "scheduler")) {
			parameter.getString("GMappingTask", "scheduler", connections.gMappingTask.scheduler);
		}
		if(parameter.checkIfParameterExists("GMappingTask", "priority")) {
			parameter.getInteger("GMappingTask", "priority", connections.gMappingTask.priority);
		}
		if(parameter.checkIfParameterExists("GMappingTask", "cpuAffinity")) {
			parameter.getInteger("GMappingTask", "cpuAffinity", connections.gMappingTask.cpuAffinity);
		}
		
		// load parameters for ComponentGMappingROSExtension
		
		// load parameters for PlainOpcUaComponentGMappingExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}