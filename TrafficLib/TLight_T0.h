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
//
//
#pragma once
#include "stdafx.h"
namespace  TrafficLib
{
	class TRAFFICLIB_API CTL_State 
	{
	public:
		CTL_State()
		{
			nlamp = RED;
			nId = 1;				// Traffic-light id
		};
		CTL_State& operator = (const CTL_State& src)
		{
			if (this == &src)
				return *this;
			nlamp = src.nlamp;
			nId = src.nId;
			return *this;
		}
		~CTL_State() {};
		void GetCanState(tCAN& cs_tl)
		{
			/*
			//			BYTE 0		: t t t i i i i i 		    :	t-> sending node type      0 0 0  cross-host traffic light
			                                                                                   0 0 1  traffic light
																							   0 1 0  pedestrian light
																							   0 1 1  pedestrian button
																							   1 0 0  counter-1
																							   1 0 2  counter-2

			//                                                      i-> sending node id        
			//			BYTE 1		: can msg type
			//			BYTE 2		: lamp  				    :	
			*/
			BYTE t = 1;
			cs_tl.data[0] = (t << 5) | (0x1F & nId);
			cs_tl.data[1] = CMS_BROADCAST;
			cs_tl.data[2] = nlamp;

			cs_tl.data[3] = 0;
			cs_tl.data[4] = 0;
			cs_tl.data[5] = 0;
			cs_tl.data[6] = 0;
			cs_tl.data[7] = 0;
		}
		BYTE nlamp;
		BYTE nId;
	};
	class TRAFFICLIB_API CTLight_T0
	{
	public:
		CTLight_T0();
		~CTLight_T0();
		void InsertNodeInterface(ICAN_Node** pNodeInterface);
		void static CallBackFunction(void** ppObject, BYTE* f, BYTE size);
		void sycroniseLOCALS();
		CTL_State& GetState();
		bool setget_PDO(tCAN& msg, bool set = true);						// (via can bus other) node PDO[] -> other object PDO[]
		void decide();

	protected:
		virtual void CAN_execute(BYTE * msg, BYTE size);
		ICAN_Node *m_pICAN_Nod;
		CTL_State m_nState;

		BYTE		 m_PDO[NUM_CAN_OBJECTS][8];		// update through can interface
			
													// local 
		int m_nGreenCounter;
		int m_nRedCounter;

	};
}	// name space

