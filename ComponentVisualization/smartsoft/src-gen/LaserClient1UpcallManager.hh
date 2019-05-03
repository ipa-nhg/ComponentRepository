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
#ifndef _LASERCLIENT1_UPCALL_MANAGER_HH
#define _LASERCLIENT1_UPCALL_MANAGER_HH

#include <list>
#include "aceSmartSoft.hh"
#include "LaserClient1UpcallInterface.hh"

/** LaserClient1UpcallManager connects input-handling with Upcall propagation
 *
 * This class implements an InputHandler for the InputPort laserClient1 and propagates the handling 
 * of incoming data to all associated (i.e. attached) Upcalls.
 */
class LaserClient1UpcallManager
:	public Smart::IInputHandler<CommBasicObjects::CommMobileLaserScan>
{
private:
	// list of associated updalls
	std::list<LaserClient1UpcallInterface*> upcalls;

	// call the on_laserClient1 of all the attached LaserClient1UpcallInterfaces
	void notify_upcalls(const CommBasicObjects::CommMobileLaserScan &input);
	
protected:
	virtual void handle_input(const CommBasicObjects::CommMobileLaserScan &input) {
		// relay input-handling to all attached LaserClient1UpcallInterfaces
		this->notify_upcalls(input);
	}
public:
	LaserClient1UpcallManager(
		Smart::InputSubject<CommBasicObjects::CommMobileLaserScan> *subject,
		const int &prescaleFactor=1
	);
	virtual ~LaserClient1UpcallManager();
	
	void attach(LaserClient1UpcallInterface *upcall);
	void detach(LaserClient1UpcallInterface *upcall);
};

#endif