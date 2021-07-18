#pragma once

namespace TrafficLib
{
	class TRAFFICLIB_API CVehicle;
	class TRAFFICLIB_API CReflector
	{
	public:
		static CReflector* me;
		static CReflector* GetReflector();
		static void KillReflector(bool bDeleteObj = false);
		
		
		static void DeleteObjectList();
		
		void addObstruction(CVehicle& rV, bool bHead = true);
		CVehicle* GetFirst();
		CVehicle* GetLast();
		CVehicle* Next();
		void Set_TLS(CTL_State& rTL);
		CTL_State& Get_TLS();

		bool Measure(CVehicle * pRefVehicle, int& nBackDistance, int& nFortDistance);
		protected:
		CReflector() ;
		~CReflector();
		L_List<CVehicle>  m_linked_List;
		CTL_State* m_pTls;
	};

} // name space 

