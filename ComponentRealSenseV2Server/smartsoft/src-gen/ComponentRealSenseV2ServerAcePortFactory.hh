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

#ifndef COMPONENTREALSENSEV2SERVER_ACE_PORTFACTORY_HH_
#define COMPONENTREALSENSEV2SERVER_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "ComponentRealSenseV2ServerImpl.hh"

// include the main component-definition class
#include "ComponentRealSenseV2ServerPortFactoryInterface.hh"

class ComponentRealSenseV2ServerAcePortFactory: public ComponentRealSenseV2ServerPortFactoryInterface
{
private:
	ComponentRealSenseV2ServerImpl *componentImpl;
public:
	ComponentRealSenseV2ServerAcePortFactory();
	virtual ~ComponentRealSenseV2ServerAcePortFactory();

	virtual void initialize(ComponentRealSenseV2Server *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IPushClientPattern<CommManipulatorObjects::CommMobileManipulatorState> * createUrPosePushTimedClient() override;
	virtual Smart::IQueryClientPattern<CommBasicObjects::CommVoid, CommManipulatorObjects::CommMobileManipulatorState,SmartACE::QueryId> * createUrPoseQueryClient() override;
	virtual Smart::IPushClientPattern<CommBasicObjects::CommBaseState> * createBasePushTimedClient() override;
	virtual Smart::IPushClientPattern<CommBasicObjects::CommDevicePoseState> * createPtuPosePushNewestClient() override;
	
	virtual Smart::IPushServerPattern<DomainVision::CommVideoImage> * createColorImagePushNewestServer(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, DomainVision::CommVideoImage,SmartACE::QueryId> * createColorImageQueryServer(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<DomainVision::CommDepthImage> * createDepthPushNewestServer(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<DomainVision::CommRGBDImage> * createImagePushNewestServer(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, DomainVision::CommRGBDImage,SmartACE::QueryId> * createImageQueryServer(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* COMPONENTREALSENSEV2SERVER_ACE_PORTFACTORY_HH_ */
