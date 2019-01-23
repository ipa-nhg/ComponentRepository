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
#include "ComponentPushClient.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "ComponentPushClientAcePortFactory.hh"


// initialize static singleton pointer to zero
ComponentPushClient* ComponentPushClient::_componentPushClient = 0;

// constructor
ComponentPushClient::ComponentPushClient()
{
	std::cout << "constructor of ComponentPushClient\n";
	
	// set all pointer members to NULL
	joystickActivity = NULL;
	joystickActivityTrigger = NULL;
	joystickServiceIn = NULL;
	joystickServiceInInputTaskTrigger = NULL;
	joystickServiceInUpcallManager = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	
	// set default ini parameter values
	connections.component.name = "ComponentPushClient";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.joystickServiceIn.wiringName = "JoystickServiceIn";
	connections.joystickServiceIn.serverName = "unknown";
	connections.joystickServiceIn.serviceName = "unknown";
	connections.joystickServiceIn.interval = 1;
	connections.joystickServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.joystickActivity.minActFreq = 0.0;
	connections.joystickActivity.maxActFreq = 0.0;
	connections.joystickActivity.trigger = "DataTriggered";
	connections.joystickActivity.inPortRef = "JoystickServiceIn";	
	connections.joystickActivity.prescale = 1;
	// scheduling default parameters
	connections.joystickActivity.scheduler = "DEFAULT";
	connections.joystickActivity.priority = -1;
	connections.joystickActivity.cpuAffinity = -1;
	
	// initialize members of ComponentPushClientROSExtension
	
	// initialize members of SeRoNetSDKComponentGeneratorExtension
	
	// initialize members of PlainOpcUaComponentPushClientExtension
	
}

void ComponentPushClient::addPortFactory(const std::string &name, ComponentPushClientPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void ComponentPushClient::addExtension(ComponentPushClientExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void ComponentPushClient::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode ComponentPushClient::connectJoystickServiceIn(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = joystickServiceIn->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->joystickServiceIn->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	joystickServiceIn->subscribe(connections.joystickServiceIn.interval);
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode ComponentPushClient::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectJoystickServiceIn(connections.joystickServiceIn.serverName, connections.joystickServiceIn.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void ComponentPushClient::startAllTasks() {
	// start task JoystickActivity
	if(connections.joystickActivity.scheduler != "DEFAULT") {
		ACE_Sched_Params joystickActivity_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.joystickActivity.scheduler == "FIFO") {
			joystickActivity_SchedParams.policy(ACE_SCHED_FIFO);
			joystickActivity_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.joystickActivity.scheduler == "RR") {
			joystickActivity_SchedParams.policy(ACE_SCHED_RR);
			joystickActivity_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		joystickActivity->start(joystickActivity_SchedParams, connections.joystickActivity.cpuAffinity);
	} else {
		joystickActivity->start();
	}
}

/**
 * Start all timers contained in this component
 */
void ComponentPushClient::startAllTimers() {
}


Smart::TaskTriggerSubject* ComponentPushClient::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "JoystickServiceIn") return joystickServiceInInputTaskTrigger;
	
	return NULL;
}


void ComponentPushClient::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		
		// initializations of ComponentPushClientROSExtension
		
		// initializations of SeRoNetSDKComponentGeneratorExtension
		
		// initializations of PlainOpcUaComponentPushClientExtension
		
		
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
		
		ComponentPushClientPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<ComponentPushClientAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition ComponentPushClient is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		
		// create client ports
		joystickServiceIn = portFactoryRegistry[connections.joystickServiceIn.roboticMiddleware]->createJoystickServiceIn();
		
		// create InputTaskTriggers and UpcallManagers
		joystickServiceInInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommJoystick>(joystickServiceIn);
		joystickServiceInUpcallManager = new JoystickServiceInUpcallManager(joystickServiceIn);
		
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
		if(connections.joystickServiceIn.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommJoystick>*>(joystickServiceIn)->add(wiringSlave, connections.joystickServiceIn.wiringName);
		}
		
		
		
		// create Task JoystickActivity
		joystickActivity = new JoystickActivity(component);
		// configure input-links
		joystickServiceInUpcallManager->attach(joystickActivity);
		// configure task-trigger (if task is configurable)
		if(connections.joystickActivity.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.joystickActivity.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(joystickActivity);
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				joystickActivityTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task JoystickActivity" << std::endl;
			}
		} else if(connections.joystickActivity.trigger == "DataTriggered") {
			joystickActivityTrigger = getInputTaskTriggerFromString(connections.joystickActivity.inPortRef);
			if(joystickActivityTrigger != NULL) {
				joystickActivityTrigger->attach(joystickActivity, connections.joystickActivity.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.joystickActivity.inPortRef << " as activation source for Task JoystickActivity" << std::endl;
			}
		} else
		{
			// setup default task-trigger as InputTrigger
			joystickActivityTrigger = getInputTaskTriggerFromString("JoystickServiceIn");
			if(joystickActivityTrigger != NULL) {
				joystickActivityTrigger->attach(joystickActivity, connections.joystickActivity.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort JoystickServiceIn as activation source for Task JoystickActivity" << std::endl;
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
void ComponentPushClient::run()
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
void ComponentPushClient::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	joystickServiceInUpcallManager->detach(joystickActivity);
	// unlink the TaskTrigger
	joystickActivityTrigger->detach(joystickActivity);
	delete joystickActivity;

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete joystickServiceInInputTaskTrigger;
	delete joystickServiceInUpcallManager;

	// destroy client ports
	delete joystickServiceIn;

	// destroy server ports
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
	
	// destruction of ComponentPushClientROSExtension
	
	// destruction of SeRoNetSDKComponentGeneratorExtension
	
	// destruction of PlainOpcUaComponentPushClientExtension
	
}

void ComponentPushClient::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("ComponentPushClient.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load ComponentPushClient.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: ComponentPushClient.ini parameter file not found! (using default values or command line arguments)\n";
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
		
		// load parameters for client JoystickServiceIn
		parameter.getString("JoystickServiceIn", "serviceName", connections.joystickServiceIn.serviceName);
		parameter.getString("JoystickServiceIn", "serverName", connections.joystickServiceIn.serverName);
		parameter.getString("JoystickServiceIn", "wiringName", connections.joystickServiceIn.wiringName);
		parameter.getInteger("JoystickServiceIn", "interval", connections.joystickServiceIn.interval);
		if(parameter.checkIfParameterExists("JoystickServiceIn", "roboticMiddleware")) {
			parameter.getString("JoystickServiceIn", "roboticMiddleware", connections.joystickServiceIn.roboticMiddleware);
		}
		
		
		// load parameters for task JoystickActivity
		parameter.getDouble("JoystickActivity", "minActFreqHz", connections.joystickActivity.minActFreq);
		parameter.getDouble("JoystickActivity", "maxActFreqHz", connections.joystickActivity.maxActFreq);
		parameter.getString("JoystickActivity", "triggerType", connections.joystickActivity.trigger);
		if(connections.joystickActivity.trigger == "PeriodicTimer") {
			parameter.getDouble("JoystickActivity", "periodicActFreqHz", connections.joystickActivity.periodicActFreq);
		} else if(connections.joystickActivity.trigger == "DataTriggered") {
			parameter.getString("JoystickActivity", "inPortRef", connections.joystickActivity.inPortRef);
			parameter.getInteger("JoystickActivity", "prescale", connections.joystickActivity.prescale);
		}
		if(parameter.checkIfParameterExists("JoystickActivity", "scheduler")) {
			parameter.getString("JoystickActivity", "scheduler", connections.joystickActivity.scheduler);
		}
		if(parameter.checkIfParameterExists("JoystickActivity", "priority")) {
			parameter.getInteger("JoystickActivity", "priority", connections.joystickActivity.priority);
		}
		if(parameter.checkIfParameterExists("JoystickActivity", "cpuAffinity")) {
			parameter.getInteger("JoystickActivity", "cpuAffinity", connections.joystickActivity.cpuAffinity);
		}
		
		// load parameters for ComponentPushClientROSExtension
		
		// load parameters for SeRoNetSDKComponentGeneratorExtension
		
		// load parameters for PlainOpcUaComponentPushClientExtension
		
		
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