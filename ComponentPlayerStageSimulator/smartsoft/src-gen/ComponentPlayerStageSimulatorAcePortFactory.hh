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

#ifndef COMPONENTPLAYERSTAGESIMULATOR_ACE_PORTFACTORY_HH_
#define COMPONENTPLAYERSTAGESIMULATOR_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "ComponentPlayerStageSimulatorImpl.hh"

// include the main component-definition class
#include "ComponentPlayerStageSimulatorPortFactoryInterface.hh"

class ComponentPlayerStageSimulatorAcePortFactory: public ComponentPlayerStageSimulatorPortFactoryInterface
{
private:
	ComponentPlayerStageSimulatorImpl *componentImpl;
public:
	ComponentPlayerStageSimulatorAcePortFactory();
	virtual ~ComponentPlayerStageSimulatorAcePortFactory();

	virtual void initialize(ComponentPlayerStageSimulator *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> * createBaseStateAnswerer(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<CommBasicObjects::CommBaseState> * createBaseStateServiceOut(const std::string &serviceName) override;
	virtual Smart::IEventServerPattern<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState,SmartACE::EventId> * createBatteryEventServiceOut(const std::string &serviceName, Smart::IEventTestHandler<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState> *batteryEventServiceOutEventTestHandler) override;
	virtual Smart::IPushServerPattern<CommBasicObjects::CommMobileLaserScan> * createLaserServiceOut(const std::string &serviceName) override;
	virtual Smart::ISendServerPattern<CommBasicObjects::CommBasePositionUpdate> * createLocalizationUpdateServiceIn(const std::string &serviceName) override;
	virtual Smart::ISendServerPattern<CommBasicObjects::CommNavigationVelocity> * createNavigationVelocityServiceIn(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* COMPONENTPLAYERSTAGESIMULATOR_ACE_PORTFACTORY_HH_ */
