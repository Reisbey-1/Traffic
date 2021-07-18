// file : PLightState.h
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
namespace  TrafficLib
{
	class TRAFFICLIB_API CPL_State
	{
	public:
		CPL_State()
		{
			nlamp = GREEN;
			nId = 2;
		};
		CPL_State& operator = (const CPL_State& src)
		{
			if (this == &src)
				return *this;
			nlamp = src.nlamp;
			nId = src.nId;
			return *this;
		}
		~CPL_State() {};
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
			//			BYTE 2		: lamp  				    :
			*/
			
			BYTE t = 2;
			cs_pl.data[0] = (t << 5) | (0x1F & nId);
			cs_pl.data[1] = CMS_BROADCAST;
			cs_pl.data[2] = nlamp;

			cs_pl.data[3] = 0;
			cs_pl.data[4] = 0;
			cs_pl.data[5] = 0;
			cs_pl.data[6] = 0;
			cs_pl.data[7] = 0;
		}
		BYTE nlamp;
		BYTE nId;
	};
	class TRAFFICLIB_API CPedestrianLight
	{
	public:
		CPedestrianLight();
		~CPedestrianLight();
		void InsertNodeInterface(ICAN_Node** pNodeInterface);
		void static CallBackFunction(void** ppObject, BYTE* f, BYTE size);
		void sycroniseLOCALS();
		CPL_State& GetState();
		bool setget_PDO(tCAN& msg, bool set = true);						// (via can bus other) node PDO[] -> other object PDO[]
		void decide();
	protected:
		virtual void CAN_execute(BYTE * msg, BYTE size);
		ICAN_Node *m_pICAN_Nod;
		CPL_State m_nState;
		
		BYTE		 m_PDO[NUM_CAN_OBJECTS][8];		// update through can interface

	};
}  // name space

