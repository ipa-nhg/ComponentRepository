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
#include "SmartJoystickServer.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "SmartJoystickServerAcePortFactory.hh"


// initialize static singleton pointer to zero
SmartJoystickServer* SmartJoystickServer::_smartJoystickServer = 0;

// constructor
SmartJoystickServer::SmartJoystickServer()
{
	std::cout << "constructor of SmartJoystickServer\n";
	
	// set all pointer members to NULL
	//coordinationPort = NULL;
	joystickServcieOut = NULL;
	joystickTask = NULL;
	joystickTaskTrigger = NULL;
	//smartJoystickServerParameters = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "SmartJoystickServer";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.joystickServcieOut.serviceName = "JoystickServcieOut";
	connections.joystickServcieOut.roboticMiddleware = "ACE_SmartSoft";
	// scheduling default parameters
	connections.joystickTask.scheduler = "DEFAULT";
	connections.joystickTask.priority = -1;
	connections.joystickTask.cpuAffinity = -1;
	
	// initialize members of SmartJoystickServerROSExtension
	
	// initialize members of PlainOpcUaSmartJoystickServerExtension
	
}

void SmartJoystickServer::addPortFactory(const std::string &name, SmartJoystickServerPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void SmartJoystickServer::addExtension(SmartJoystickServerExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* SmartJoystickServer::getComponentImpl()
{
	return dynamic_cast<SmartJoystickServerAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void SmartJoystickServer::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}




/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode SmartJoystickServer::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void SmartJoystickServer::startAllTasks() {
	// start task JoystickTask
	if(connections.joystickTask.scheduler != "DEFAULT") {
		ACE_Sched_Params joystickTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.joystickTask.scheduler == "FIFO") {
			joystickTask_SchedParams.policy(ACE_SCHED_FIFO);
			joystickTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.joystickTask.scheduler == "RR") {
			joystickTask_SchedParams.policy(ACE_SCHED_RR);
			joystickTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		joystickTask->start(joystickTask_SchedParams, connections.joystickTask.cpuAffinity);
	} else {
		joystickTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void SmartJoystickServer::startAllTimers() {
}


Smart::TaskTriggerSubject* SmartJoystickServer::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void SmartJoystickServer::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getParameters() << std::endl;
		
		// initializations of SmartJoystickServerROSExtension
		
		// initializations of PlainOpcUaSmartJoystickServerExtension
		
		
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
		
		SmartJoystickServerPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<SmartJoystickServerAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition SmartJoystickServer is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		joystickServcieOut = portFactoryRegistry[connections.joystickServcieOut.roboticMiddleware]->createJoystickServcieOut(connections.joystickServcieOut.serviceName);
		
		// create client ports
		
		// create InputTaskTriggers and UpcallManagers
		
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
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task JoystickTask
		joystickTask = new JoystickTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void SmartJoystickServer::run()
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
void SmartJoystickServer::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(joystickTaskTrigger != NULL){
		joystickTaskTrigger->detach(joystickTask);
		delete joystickTask;
	}

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports

	// destroy server ports
	delete joystickServcieOut;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	delete param;
	

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
	
	// destruction of SmartJoystickServerROSExtension
	
	// destruction of PlainOpcUaSmartJoystickServerExtension
	
}

void SmartJoystickServer::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("SmartJoystickServer.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load SmartJoystickServer.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: SmartJoystickServer.ini parameter file not found! (using default values or command line arguments)\n";
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
		
		
		// load parameters for server JoystickServcieOut
		parameter.getString("JoystickServcieOut", "serviceName", connections.joystickServcieOut.serviceName);
		if(parameter.checkIfParameterExists("JoystickServcieOut", "roboticMiddleware")) {
			parameter.getString("JoystickServcieOut", "roboticMiddleware", connections.joystickServcieOut.roboticMiddleware);
		}
		
		// load parameters for task JoystickTask
		if(parameter.checkIfParameterExists("JoystickTask", "scheduler")) {
			parameter.getString("JoystickTask", "scheduler", connections.joystickTask.scheduler);
		}
		if(parameter.checkIfParameterExists("JoystickTask", "priority")) {
			parameter.getInteger("JoystickTask", "priority", connections.joystickTask.priority);
		}
		if(parameter.checkIfParameterExists("JoystickTask", "cpuAffinity")) {
			parameter.getInteger("JoystickTask", "cpuAffinity", connections.joystickTask.cpuAffinity);
		}
		
		// load parameters for SmartJoystickServerROSExtension
		
		// load parameters for PlainOpcUaSmartJoystickServerExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
		paramHandler.loadParameter(parameter);
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
