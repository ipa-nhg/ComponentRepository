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
#ifndef _COMPONENTSYMBOLICPLANNERIMPL_HH
#define _COMPONENTSYMBOLICPLANNERIMPL_HH

#include "aceSmartSoft.hh"

class ComponentSymbolicPlannerImpl : public SmartACE::SmartComponent {
public:
	ComponentSymbolicPlannerImpl(const std::string &componentName, int & argc, char ** argv);
	ComponentSymbolicPlannerImpl(const std::string &componentName, int & argc, char ** argv, const ACE_Sched_Params &sched_params);
	virtual ~ComponentSymbolicPlannerImpl();

	Smart::StatusCode run(void);
	void closeAllAssociatedTasks(const int &taskShutdownTimeLimit);
	void cleanUpComponentResources();
};

#endif
