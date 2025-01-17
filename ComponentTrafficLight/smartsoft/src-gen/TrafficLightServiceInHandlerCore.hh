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
#ifndef _TRAFFICLIGHTSERVICEINHANDLER_CORE_HH
#define _TRAFFICLIGHTSERVICEINHANDLER_CORE_HH

#include <aceSmartSoft.hh>

// include the main input-handler interface
#include "TrafficLightServiceInUpcallInterface.hh"
// include all other input interfaces (if any)

// include all interaction-observer interfaces
#include <TrafficLightServiceInHandlerObserverInterface.hh>

class TrafficLightServiceInHandlerCore
:	public Smart::InputTaskTrigger<DomainHMI::CommTrafficLight>
,	public TrafficLightServiceInUpcallInterface
{
private:
	Smart::StatusCode updateStatus;
	DomainHMI::CommTrafficLight lastUpdate;
	
	
	virtual void updateAllCommObjects();
	
	// internal input handling method
	virtual void handle_input(const DomainHMI::CommTrafficLight& input) {
		this->updateAllCommObjects();
		// call the input handler method (which has to be implemented in derived classes)
		this->on_TrafficLightServiceIn(input);
		// notify all attached interaction observers
		this->notify_all_interaction_observers();
		// call implementation of base class
		Smart::InputTaskTrigger<DomainHMI::CommTrafficLight>::handle_input(input);
	}
	
/**
 * Implementation of the Subject part of an InteractionObserver
 */
private:
	std::mutex interaction_observers_mutex;
	std::list<TrafficLightServiceInHandlerObserverInterface*> interaction_observers;
protected:
	void notify_all_interaction_observers();
public:
	void attach_interaction_observer(TrafficLightServiceInHandlerObserverInterface *observer);
	void detach_interaction_observer(TrafficLightServiceInHandlerObserverInterface *observer);
	
protected:

public:
	TrafficLightServiceInHandlerCore(
		Smart::InputSubject<DomainHMI::CommTrafficLight> *subject,
		const int &prescaleFactor=1);
	virtual ~TrafficLightServiceInHandlerCore();
};
#endif
