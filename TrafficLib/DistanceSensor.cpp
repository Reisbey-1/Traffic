#include "stdafx.h"
#include "DistanceSensor.h"
namespace TrafficLib
{


	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////

	CDistanceSensor::CDistanceSensor()
	{
	//	m_nDistance = 0;
		m_pParent = NULL;
	//	m_pReflector = CReflector::GetReflector();
	}
	CDistanceSensor::CDistanceSensor(CVehicle * pParent)
	{
		m_nDistance = 0;
		m_pParent = pParent;
	}


	CDistanceSensor::~CDistanceSensor()
	{
	}
	
	int  CDistanceSensor::measure_front_distance()
	{
		// meause distance and update member m_nDistance
		// possible simulation model for the sensor
		//		1)	- may send a request to the scheduler object if there is an other vehicle(s) in the vicinity.
		//			- if there is a one, schedular send responce message with the other_vehicle state.
		//			- calculate the distance to closest one. Return the distance as read-out of sensor.
		//			- Schedular must keep actual position of all registered vehicles. 
		//			- all communication run on WiFi
		//
		//		2)	- vehicle-object enumaretes all other vehicle-objects. 
		//			- determines obtrucle object in the vicinity if there is a one.
		//			- returns distance to obstruct as read-out of sensor.
		//          - communication run on WiFi
		// 
		//		3)	- a new singleton reflector object  created
		//			- in reflector-objet a linked-chain-list of CVehicle& objects is created
		//			- each veichle-sensor iterates on the list and measur the distance of privous and next vehicle 
		//          - calculated values are the back and fort distance

		int nBackDistance = 0, nFortDistance = 0;
		CReflector::GetReflector()->Measure(m_pParent, nBackDistance, nFortDistance);

					//m_pParent->halt();
		return		nFortDistance;
	}

	int  CDistanceSensor::measure_back_distance()
	{
		// meause distance and update member m_nDistance
		// possible simulation model for the sensor
		//		1)	- may send a request to the scheduler object if there is an other vehicle(s) in the vicinity.
		//			- if there is a one, schedular send responce message with the other_vehicle state.
		//			- calculate the distance to closest one. Return the distance as read-out of sensor.
		//			- Schedular must keep actual position of all registered vehicles. 
		//			- all communication run on WiFi
		//
		//		2)	- vehicle-object enumaretes all other vehicle-objects. 
		//			- determines obtrucle object in the vicinity if there is a one.
		//			- returns distance to obstruct as read-out of sensor.
		//          - communication run on WiFi
		// 
		//		3)	- a new singleton reflector object  created
		//			- in reflector-objet a linked-chain-list of CVehicle& objects is created
		//			- each veichle-sensor iterates on the list and measur the distance of privous and next vehicle 
		//          - calculated values are the back and fort distance

		int nBackDistance = 0, nFortDistance = 0;
		CReflector::GetReflector()->Measure(m_pParent, nBackDistance, nFortDistance);

		//m_pParent->halt();
		return		nBackDistance;
	}
} // name space
