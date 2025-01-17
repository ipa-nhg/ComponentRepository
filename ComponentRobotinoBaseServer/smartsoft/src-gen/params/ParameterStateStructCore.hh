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
#ifndef _PARAMETERSTATESTRUCTCORE_HH
#define _PARAMETERSTATESTRUCTCORE_HH

#include "aceSmartSoft.hh"

#include <iostream>

// forward declaration (in order to define validateCOMMIT(ParameterStateStruct) which is implemented in derived class)
class ParameterStateStruct;

class ParameterStateStructCore
{
	friend class ParamUpdateHandler;
public:
	
		///////////////////////////////////////////
		// Internal params
		///////////////////////////////////////////
		
		/**
		 * Definition of Parameter Robot
		 */
		class RobotType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			std::string daemonIP;
			double maxRotVel;
			double maxVelX;
			double maxVelY;
		
		public:
			// default constructor
			RobotType() {
				daemonIP = "127.0.0.1";
				maxRotVel = 4.0;
				maxVelX = 1.0;
				maxVelY = 1.0;
			}
		
			/**
			 * here are the public getters
			 */
			inline std::string getDaemonIP() const { return daemonIP; }
			inline double getMaxRotVel() const { return maxRotVel; }
			inline double getMaxVelX() const { return maxVelX; }
			inline double getMaxVelY() const { return maxVelY; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "Robot(";
				os << "daemonIP = " << daemonIP << ", ";
				os << "maxRotVel = " << maxRotVel << ", ";
				os << "maxVelX = " << maxVelX << ", ";
				os << "maxVelY = " << maxVelY << ", ";
				os << ")\n";
			}
			
		}; // end class RobotType
		
		/**
		 * Definition of Parameter Bumper
		 */
		class BumperType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			int bumperTimeOutMSec;
			int bumperTimeOutSec;
		
		public:
			// default constructor
			BumperType() {
				bumperTimeOutMSec = 0;
				bumperTimeOutSec = 10;
			}
		
			/**
			 * here are the public getters
			 */
			inline int getBumperTimeOutMSec() const { return bumperTimeOutMSec; }
			inline int getBumperTimeOutSec() const { return bumperTimeOutSec; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "Bumper(";
				os << "bumperTimeOutMSec = " << bumperTimeOutMSec << ", ";
				os << "bumperTimeOutSec = " << bumperTimeOutSec << ", ";
				os << ")\n";
			}
			
		}; // end class BumperType
		
		/**
		 * Definition of Parameter LaserSafetyField
		 */
		class LaserSafetyFieldType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			bool generateLaserSafetyFieldEvents;
			int laserSafetyfFieldTimeOutMSec;
			int laserSafetyfFieldTimeOutSec;
		
		public:
			// default constructor
			LaserSafetyFieldType() {
				generateLaserSafetyFieldEvents = false;
				laserSafetyfFieldTimeOutMSec = 0;
				laserSafetyfFieldTimeOutSec = 10;
			}
		
			/**
			 * here are the public getters
			 */
			inline bool getGenerateLaserSafetyFieldEvents() const { return generateLaserSafetyFieldEvents; }
			inline int getLaserSafetyfFieldTimeOutMSec() const { return laserSafetyfFieldTimeOutMSec; }
			inline int getLaserSafetyfFieldTimeOutSec() const { return laserSafetyfFieldTimeOutSec; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "LaserSafetyField(";
				os << "generateLaserSafetyFieldEvents = " << generateLaserSafetyFieldEvents << ", ";
				os << "laserSafetyfFieldTimeOutMSec = " << laserSafetyfFieldTimeOutMSec << ", ";
				os << "laserSafetyfFieldTimeOutSec = " << laserSafetyfFieldTimeOutSec << ", ";
				os << ")\n";
			}
			
		}; // end class LaserSafetyFieldType
		
		/**
		 * Definition of Parameter General
		 */
		class GeneralType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			bool hasSignalState;
			std::string poseFileName;
			bool useLocalizationEvent;
			bool verbose;
			bool writePoseFile;
		
		public:
			// default constructor
			GeneralType() {
				hasSignalState = true;
				poseFileName = "/tmp/lastRobotPose.txt";
				useLocalizationEvent = true;
				verbose = false;
				writePoseFile = false;
			}
		
			/**
			 * here are the public getters
			 */
			inline bool getHasSignalState() const { return hasSignalState; }
			inline std::string getPoseFileName() const { return poseFileName; }
			inline bool getUseLocalizationEvent() const { return useLocalizationEvent; }
			inline bool getVerbose() const { return verbose; }
			inline bool getWritePoseFile() const { return writePoseFile; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "General(";
				os << "hasSignalState = " << hasSignalState << ", ";
				os << "poseFileName = " << poseFileName << ", ";
				os << "useLocalizationEvent = " << useLocalizationEvent << ", ";
				os << "verbose = " << verbose << ", ";
				os << "writePoseFile = " << writePoseFile << ", ";
				os << ")\n";
			}
			
		}; // end class GeneralType
		
	
		///////////////////////////////////////////
		// External params
		///////////////////////////////////////////
		
	
		///////////////////////////////////////////
		// Instance params
		///////////////////////////////////////////
		
		/**
		 * Definition of instantiated ParameterRepository CommBasicObjects
		 */
		class CommBasicObjectsType {
			friend class ParamUpdateHandler;
			public:
			/**
			 * Definition of instantiated ParameterSet BaseParams
			 */
			class BaseParamsType {
				friend class ParamUpdateHandler;
				public:
				protected:
					/**
					 * internal members
					 */
					
				public:
					/**
					 * public getter methods
					 */
					
					void to_ostream(std::ostream &os = std::cout) const
					{
						os << "BaseParams(\n";
						os << ")";
					}
			}; // end of parameter-set class BaseParamsType
			
			protected:
				/**
				 * internal members
				 */
				BaseParamsType BaseParams;
			
			public:
				/**
				 * public getter methods
				 */
				inline BaseParamsType getBaseParams() const { return BaseParams; }
				
				void to_ostream(std::ostream &os = std::cout) const
				{
					os << "CommBasicObjects(\n";
					BaseParams.to_ostream(os);
					os << ")";
				}
		}; // end of parameter-repository wrapper class CommBasicObjectsType
	
protected:

	// Internal params
	BumperType Bumper;
	GeneralType General;
	LaserSafetyFieldType LaserSafetyField;
	RobotType Robot;
	
	// External params
	
	// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
	CommBasicObjectsType CommBasicObjects;
	

	void setContent(const ParameterStateStructCore &commit) {
		// External params
	
		this->CommBasicObjects = commit.getCommBasicObjects();
	}

	// special trigger method (user upcall) called before updating parameter global state
	virtual SmartACE::ParamResponseType handleCOMMIT(const ParameterStateStruct &commitState) = 0;
public:
	ParameterStateStructCore() {  }
	virtual ~ParameterStateStructCore() {  }
	
	// internal param getters
	BumperType getBumper() const {
		return Bumper;
	}
	GeneralType getGeneral() const {
		return General;
	}
	LaserSafetyFieldType getLaserSafetyField() const {
		return LaserSafetyField;
	}
	RobotType getRobot() const {
		return Robot;
	}
	
	// external param getters
	
	// repo wrapper class getter(s)
	CommBasicObjectsType getCommBasicObjects() const {
		return CommBasicObjects;
	}
	
	// helper method to easily implement output stream in derived classes
	void to_ostream(std::ostream &os = std::cout) const
	{
		// Internal params
		Bumper.to_ostream(os);
		General.to_ostream(os);
		LaserSafetyField.to_ostream(os);
		Robot.to_ostream(os);
		
		// External params
		
		// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
		CommBasicObjects.to_ostream(os);
	}
};

#endif
