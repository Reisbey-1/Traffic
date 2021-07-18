
///
///  NUM_CAN_OBJECTS : 6
///
///  BYTE m_nPDO [NUM_CAN_OBJECTS] [8]
///	==================================
///          ______________________
///         |                      |   
///         |   cross-host         |   0:
///         |______________________|   
///         |                      |   
///         |   traffic-light      |   1:
///         |______________________|   
///         |                      |   
///         |   pedestrian-light   |   2:
///         |______________________|   
///         |                      |   
///         |   pedestrian-button  |   3:
///         |______________________|   
///         |                      |   
///         |   counter-1          |   4:
///         |______________________|   
///         |                      |   
///         |   counter-2          |   5:
///         |______________________| 
#pragma once
#include "stdafx.h"
#include "TrafficLib_Globals.h"
namespace TrafficLib
{
	//typedef  void(*pCanCallBack_CH) (BYTE * msg, BYTE size);
	class TRAFFICLIB_API CCH_State
	{
	public:
		CCH_State()
		{
			nId = 0;					
		};
		CCH_State& operator = (const CCH_State& src)
		{
			if (this == &src)
				return *this;
			nId = src.nId;
			return *this;

		}
		~CCH_State() {};
		void GetCanState(tCAN& cs_pl)
		{
			/*
			//			BYTE 0		: t t t i i i i i 		    :	t-> sending node type		0 0 0  cross-host traffic light
																								0 0 1  traffic light
																								0 1 0  pedestrian light
																								0 1 1  pedestrian button
																								1 0 0  counter-1
																								1 0 2  counter-2

			//                                                      i-> sending node id
			//			BYTE 1		: can msg type
			//			BYTE 2		: 
			*/
			BYTE t = 0;
			cs_pl.data[0] = (t << 5) | (0x1F & nId);
			cs_pl.data[1] = CMS_BROADCAST;
			cs_pl.data[2] = 0;

			cs_pl.data[3] = 0;
			cs_pl.data[4] = 0;
			cs_pl.data[5] = 0;
			cs_pl.data[6] = 0;
			cs_pl.data[7] = 0;
		}
		BYTE nId;
	};

	class TRAFFICLIB_API ICrossHost  : public  IInternetObject
	{		
	/*	
		virtual void move_forward() = 0;
		virtual void move_backward() = 0;
		virtual void halt() = 0;
		virtual void draw(long** ppDC, long** ppObject) = 0;
		virtual void set_previos(CVehicle * p) = 0;
		virtual void set_next(CVehicle * p) = 0;
		virtual void get_Telegram(sTCP_IP_TLG& tlg) = 0;
*/
		virtual void get_Telegram(sTCP_IP_TLG& tlg) = 0;
	};


	class TRAFFICLIB_API CCrossHost	  : public ICrossHost
	{
	public:
		CCrossHost();
		~CCrossHost();
		////////
		void InsertNodeInterface(ICAN_Node** pNodeInterface);
		void static CallBackFunction(void** ppObject, BYTE* f, BYTE size);
		void sycroniseLOCALS();
		CCH_State& GetState();
		bool setget_PDO(tCAN& msg, bool set = true);						// (via can bus other) node PDO[] -> other object PDO[]
		void decide();
		////////

		// IInternetObject ///////////////////////////////////////
		virtual void RcvTlg(const sTCP_IP_TLG tlg) ;
		virtual void RlsTlg(sTCP_IP_TLG& tlg) ;
		virtual sTCP_IP_ADDRESS get_IP_adress() ;


	protected:
		virtual void TCP_execute(sTCP_IP_TLG& tlg);
		virtual void CAN_execute(BYTE * msg, BYTE size);
		ICAN_Node *m_pICAN_Nod;
		//////////////////////////////////////////////////////////

	public:
		virtual void get_Telegram(sTCP_IP_TLG& tlg) ;


		///  C A N  ///
	protected:	
		CCH_State m_nState;
		BYTE		 m_PDO[NUM_CAN_OBJECTS][8];		// update through can interface

	};

}	// name space