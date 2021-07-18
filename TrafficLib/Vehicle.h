#pragma once
/*
			 
			|----=----------=----|
   o--------|                    |---------------------------------------------------> x
			|----=----------=----|
			     
				 ====>  direction positive
				 <====  direction negative
				 =====  direction null (halt)
				
*/
#include "DistanceSensor.h"
#include "TrafficLib_Globals.h"

namespace TrafficLib
{
	//class CVehicle;
	//typedef  void(*pCallBackFunction) (void** ppObject, BYTE * data, BYTE size);

	class TRAFFICLIB_API CVehicleState
	{
	public:
		CVehicleState() {
			m_nPos = 0;
			m_nSpeed = 0;
			m_nAxis = 0;

		};
		~CVehicleState() {};

		int m_nPos;
		int m_nSpeed;
		int m_nAxis;

	
	protected:

	};
	class TRAFFICLIB_API IVehicle : public  IInternetObject
	{
	
		virtual void move_forward()		= 0;
		virtual void move_backward()	= 0;
		virtual void halt()				= 0;
		virtual void get_state(CVehicleState &s)	= 0;
		virtual void get_Telegram(sTCP_IP_TLG& tlg) = 0;
	
	};

	class TRAFFICLIB_API CVehicle : public IVehicle
	{
	public:
		CVehicle();
		CVehicle(sTCP_IP_ADDRESS& adr, int Pos = 0, int axis= 0, int velocit = 1);
		~CVehicle();
		/// interface member functions
		void move_forward();
		void move_backward();
		void halt();
		virtual void get_state(CVehicleState &s);
		virtual void run() ;
		bool operator == (const CVehicle& src) const
		{
			return true; // ((pNext == src.pNext) && (pPrev == src.pPrev) && (pObj == src.pPrev));
		}
		///////////
		virtual void RcvTlg(const sTCP_IP_TLG tlg) ;
		virtual void RlsTlg(sTCP_IP_TLG& tlg) ;
		virtual void get_Telegram(sTCP_IP_TLG& tlg) ;
		virtual sTCP_IP_ADDRESS get_IP_adress() ;
		int m_nPos;
		int m_nAxis;
	protected:
		virtual void TCP_execute(sTCP_IP_TLG& tlg);
		
		///
	protected:
		int m_nSpeed;

		CDistanceSensor* m_pSensor;
	};
}  // name space

