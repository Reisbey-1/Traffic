#pragma once

namespace TrafficLib
{
	class CVehicle;
	class TRAFFICLIB_API CDistanceSensor
	{
	public:
		CDistanceSensor();
		CDistanceSensor(CVehicle * pParent);
		~CDistanceSensor();
//		int GetDistance();			// distance to obstruct
		int measure_front_distance();
		int measure_back_distance();
	protected:
		int m_nSensorId;
		int m_nDistance;
		CVehicle * m_pParent;
	//	CReflector * m_pReflector;
		
	};
} // name space 

