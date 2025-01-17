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

#ifndef SMARTGAZEBOBASESERVER_ACE_PORTFACTORY_HH_
#define SMARTGAZEBOBASESERVER_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "SmartGazeboBaseServerImpl.hh"

// include the main component-definition class
#include "SmartGazeboBaseServerPortFactoryInterface.hh"

class SmartGazeboBaseServerAcePortFactory: public SmartGazeboBaseServerPortFactoryInterface
{
private:
	SmartGazeboBaseServerImpl *componentImpl;
public:
	SmartGazeboBaseServerAcePortFactory();
	virtual ~SmartGazeboBaseServerAcePortFactory();

	virtual void initialize(SmartGazeboBaseServer *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> * createBaseSatateQueryAnsw(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<CommBasicObjects::CommBaseState> * createBaseStateServiceOut(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<CommBasicObjects::CommMobileLaserScan> * createLaserServiceOut(const std::string &serviceName) override;
	virtual Smart::ISendServerPattern<CommBasicObjects::CommBasePositionUpdate> * createLocalizationUpdateServiceIn(const std::string &serviceName) override;
	virtual Smart::ISendServerPattern<CommBasicObjects::CommNavigationVelocity> * createNavVelServiceIn(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* SMARTGAZEBOBASESERVER_ACE_PORTFACTORY_HH_ */
