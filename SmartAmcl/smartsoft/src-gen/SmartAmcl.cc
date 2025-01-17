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
#include "SmartAmcl.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "SmartAmclAcePortFactory.hh"

#include "LocalizationEventServiceOutEventTestHandler.hh"

// initialize static singleton pointer to zero
SmartAmcl* SmartAmcl::_smartAmcl = 0;

// constructor
SmartAmcl::SmartAmcl()
{
	std::cout << "constructor of SmartAmcl\n";
	
	// set all pointer members to NULL
	amclTask = NULL;
	amclTaskTrigger = NULL;
	//coordinationPort = NULL;
	laserServiceIn = NULL;
	laserServiceInInputTaskTrigger = NULL;
	laserServiceInUpcallManager = NULL;
	localizationEventServiceOut = NULL;
	localizationEventServiceOutEventTestHandler = NULL; 
	localizationUpdateServiceOut = NULL;
	//smartAmclParams = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "SmartAmcl";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.localizationEventServiceOut.serviceName = "LocalizationEventServiceOut";
	connections.localizationEventServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.laserServiceIn.wiringName = "LaserServiceIn";
	connections.laserServiceIn.serverName = "unknown";
	connections.laserServiceIn.serviceName = "unknown";
	connections.laserServiceIn.interval = 1;
	connections.laserServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.localizationUpdateServiceOut.initialConnect = false;
	connections.localizationUpdateServiceOut.wiringName = "LocalizationUpdateServiceOut";
	connections.localizationUpdateServiceOut.serverName = "unknown";
	connections.localizationUpdateServiceOut.serviceName = "unknown";
	connections.localizationUpdateServiceOut.interval = 1;
	connections.localizationUpdateServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.amclTask.minActFreq = 0.0;
	connections.amclTask.maxActFreq = 0.0;
	connections.amclTask.trigger = "DataTriggered";
	connections.amclTask.inPortRef = "LaserServiceIn";	
	connections.amclTask.prescale = 1;
	// scheduling default parameters
	connections.amclTask.scheduler = "DEFAULT";
	connections.amclTask.priority = -1;
	connections.amclTask.cpuAffinity = -1;
	
	// initialize members of SmartAmclROSExtension
	
	// initialize members of PlainOpcUaSmartAmclExtension
	
}

void SmartAmcl::addPortFactory(const std::string &name, SmartAmclPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void SmartAmcl::addExtension(SmartAmclExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* SmartAmcl::getComponentImpl()
{
	return dynamic_cast<SmartAmclAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void SmartAmcl::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode SmartAmcl::connectLaserServiceIn(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = laserServiceIn->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->laserServiceIn->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	laserServiceIn->subscribe(connections.laserServiceIn.interval);
	return status;
}
Smart::StatusCode SmartAmcl::connectLocalizationUpdateServiceOut(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.localizationUpdateServiceOut.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = localizationUpdateServiceOut->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->localizationUpdateServiceOut->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode SmartAmcl::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectLaserServiceIn(connections.laserServiceIn.serverName, connections.laserServiceIn.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectLocalizationUpdateServiceOut(connections.localizationUpdateServiceOut.serverName, connections.localizationUpdateServiceOut.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void SmartAmcl::startAllTasks() {
	// start task AmclTask
	if(connections.amclTask.scheduler != "DEFAULT") {
		ACE_Sched_Params amclTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.amclTask.scheduler == "FIFO") {
			amclTask_SchedParams.policy(ACE_SCHED_FIFO);
			amclTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.amclTask.scheduler == "RR") {
			amclTask_SchedParams.policy(ACE_SCHED_RR);
			amclTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		amclTask->start(amclTask_SchedParams, connections.amclTask.cpuAffinity);
	} else {
		amclTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void SmartAmcl::startAllTimers() {
}


Smart::TaskTriggerSubject* SmartAmcl::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "LaserServiceIn") return laserServiceInInputTaskTrigger;
	
	return NULL;
}


void SmartAmcl::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getParameters() << std::endl;
		
		// initializations of SmartAmclROSExtension
		
		// initializations of PlainOpcUaSmartAmclExtension
		
		
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
		
		SmartAmclPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<SmartAmclAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition SmartAmcl is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		localizationEventServiceOutEventTestHandler = new LocalizationEventServiceOutEventTestHandler();
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		localizationEventServiceOut = portFactoryRegistry[connections.localizationEventServiceOut.roboticMiddleware]->createLocalizationEventServiceOut(connections.localizationEventServiceOut.serviceName, localizationEventServiceOutEventTestHandler);
		
		// create client ports
		laserServiceIn = portFactoryRegistry[connections.laserServiceIn.roboticMiddleware]->createLaserServiceIn();
		localizationUpdateServiceOut = portFactoryRegistry[connections.localizationUpdateServiceOut.roboticMiddleware]->createLocalizationUpdateServiceOut();
		
		// create InputTaskTriggers and UpcallManagers
		laserServiceInInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan>(laserServiceIn);
		laserServiceInUpcallManager = new LaserServiceInUpcallManager(laserServiceIn);
		
		// create input-handler
		
		// create request-handlers
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		if (stateSlave->defineStates("Active" ,"active") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion Active.active" << std::endl;
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		if(connections.laserServiceIn.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommMobileLaserScan>*>(laserServiceIn)->add(wiringSlave, connections.laserServiceIn.wiringName);
		}
		if(connections.localizationUpdateServiceOut.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::SendClient<CommBasicObjects::CommBasePositionUpdate>*>(localizationUpdateServiceOut)->add(wiringSlave, connections.localizationUpdateServiceOut.wiringName);
		}
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task AmclTask
		amclTask = new AmclTask(component);
		// configure input-links
		laserServiceInUpcallManager->attach(amclTask);
		// configure task-trigger (if task is configurable)
		if(connections.amclTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.amclTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(amclTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				amclTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task AmclTask" << std::endl;
			}
		} else if(connections.amclTask.trigger == "DataTriggered") {
			amclTaskTrigger = getInputTaskTriggerFromString(connections.amclTask.inPortRef);
			if(amclTaskTrigger != NULL) {
				amclTaskTrigger->attach(amclTask, connections.amclTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.amclTask.inPortRef << " as activation source for Task AmclTask" << std::endl;
			}
		} else
		{
			// setup default task-trigger as InputTrigger
			amclTaskTrigger = getInputTaskTriggerFromString("LaserServiceIn");
			if(amclTaskTrigger != NULL) {
				amclTaskTrigger->attach(amclTask, connections.amclTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort LaserServiceIn as activation source for Task AmclTask" << std::endl;
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
void SmartAmcl::run()
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
void SmartAmcl::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	laserServiceInUpcallManager->detach(amclTask);
	// unlink the TaskTrigger
	if(amclTaskTrigger != NULL){
		amclTaskTrigger->detach(amclTask);
		delete amclTask;
	}

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete laserServiceInInputTaskTrigger;
	delete laserServiceInUpcallManager;

	// destroy client ports
	delete laserServiceIn;
	delete localizationUpdateServiceOut;

	// destroy server ports
	delete localizationEventServiceOut;
	// destroy event-test handlers (if needed)
	delete localizationEventServiceOutEventTestHandler;
	
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
	
	// destruction of SmartAmclROSExtension
	
	// destruction of PlainOpcUaSmartAmclExtension
	
}

void SmartAmcl::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("SmartAmcl.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load SmartAmcl.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: SmartAmcl.ini parameter file not found! (using default values or command line arguments)\n";
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
		
		// load parameters for client LaserServiceIn
		parameter.getString("LaserServiceIn", "serviceName", connections.laserServiceIn.serviceName);
		parameter.getString("LaserServiceIn", "serverName", connections.laserServiceIn.serverName);
		parameter.getString("LaserServiceIn", "wiringName", connections.laserServiceIn.wiringName);
		parameter.getInteger("LaserServiceIn", "interval", connections.laserServiceIn.interval);
		if(parameter.checkIfParameterExists("LaserServiceIn", "roboticMiddleware")) {
			parameter.getString("LaserServiceIn", "roboticMiddleware", connections.laserServiceIn.roboticMiddleware);
		}
		// load parameters for client LocalizationUpdateServiceOut
		parameter.getBoolean("LocalizationUpdateServiceOut", "initialConnect", connections.localizationUpdateServiceOut.initialConnect);
		parameter.getString("LocalizationUpdateServiceOut", "serviceName", connections.localizationUpdateServiceOut.serviceName);
		parameter.getString("LocalizationUpdateServiceOut", "serverName", connections.localizationUpdateServiceOut.serverName);
		parameter.getString("LocalizationUpdateServiceOut", "wiringName", connections.localizationUpdateServiceOut.wiringName);
		if(parameter.checkIfParameterExists("LocalizationUpdateServiceOut", "roboticMiddleware")) {
			parameter.getString("LocalizationUpdateServiceOut", "roboticMiddleware", connections.localizationUpdateServiceOut.roboticMiddleware);
		}
		
		// load parameters for server LocalizationEventServiceOut
		parameter.getString("LocalizationEventServiceOut", "serviceName", connections.localizationEventServiceOut.serviceName);
		if(parameter.checkIfParameterExists("LocalizationEventServiceOut", "roboticMiddleware")) {
			parameter.getString("LocalizationEventServiceOut", "roboticMiddleware", connections.localizationEventServiceOut.roboticMiddleware);
		}
		
		// load parameters for task AmclTask
		parameter.getDouble("AmclTask", "minActFreqHz", connections.amclTask.minActFreq);
		parameter.getDouble("AmclTask", "maxActFreqHz", connections.amclTask.maxActFreq);
		parameter.getString("AmclTask", "triggerType", connections.amclTask.trigger);
		if(connections.amclTask.trigger == "PeriodicTimer") {
			parameter.getDouble("AmclTask", "periodicActFreqHz", connections.amclTask.periodicActFreq);
		} else if(connections.amclTask.trigger == "DataTriggered") {
			parameter.getString("AmclTask", "inPortRef", connections.amclTask.inPortRef);
			parameter.getInteger("AmclTask", "prescale", connections.amclTask.prescale);
		}
		if(parameter.checkIfParameterExists("AmclTask", "scheduler")) {
			parameter.getString("AmclTask", "scheduler", connections.amclTask.scheduler);
		}
		if(parameter.checkIfParameterExists("AmclTask", "priority")) {
			parameter.getInteger("AmclTask", "priority", connections.amclTask.priority);
		}
		if(parameter.checkIfParameterExists("AmclTask", "cpuAffinity")) {
			parameter.getInteger("AmclTask", "cpuAffinity", connections.amclTask.cpuAffinity);
		}
		
		// load parameters for SmartAmclROSExtension
		
		// load parameters for PlainOpcUaSmartAmclExtension
		
		
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
