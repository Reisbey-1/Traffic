#include "stdafx.h"
#include "PedestrianLight.h"
namespace  TrafficLib
{
	CPedestrianLight::CPedestrianLight()
	{
		m_pICAN_Nod = NULL;
		m_pICAN_Nod = NULL;
		for (int i = 0; i< NUM_CAN_OBJECTS; i++)
			for (int j = 0; j < 8; j++)
				m_PDO[i][j] = 0;
	}
	CPedestrianLight::~CPedestrianLight()
	{
	}
	CPL_State& CPedestrianLight::GetState()
	{
		// get ls
		return m_nState;
	}

	void CPedestrianLight::InsertNodeInterface(ICAN_Node** pNodeInterface)
	{
		m_pICAN_Nod = *pNodeInterface;
	}
	void CPedestrianLight::CallBackFunction(void** ppObject, BYTE* f, BYTE size)
	{
		CPedestrianLight * self = static_cast<CPedestrianLight*>(*ppObject);
		self->CAN_execute(f, size);
	}

	void CPedestrianLight::CAN_execute(BYTE * msg, BYTE size)
	{
		/*
		//			BYTE 0		: node Id  				    :	sending node id
		//			BYTE 1		: command  				    :	sending node id
		*/
		BYTE sendingNodId = msg[0];
		BYTE type = msg[1];

		// if I did send the message  then quit
		if (sendingNodId == m_nState.nId)
			return;
		////////////////////////////////////////////////////////////////////////////

		if (type >= CMS_COMMAND)
		{
			;
		}
		else if (type == CMS_BROADCAST)
		{
			for (int i = 0; i < 8; i++)
				m_PDO[sendingNodId][i] = msg[i];
		}

	}
	void CPedestrianLight::decide()
	{


	}
	void CPedestrianLight::sycroniseLOCALS()
	{
		bool bset = true;
		tCAN can_sMsgBroadCast;
		tCAN* pCan_sMsgBroadCast;
		CPL_State ps = GetState();										// from objetc to locale state 
		ps.GetCanState(can_sMsgBroadCast);											// from state to can-msg
		can_sMsgBroadCast.id = CMS_BROADCAST;
		setget_PDO(can_sMsgBroadCast, bset);									    // Update its local part 
		if (m_pICAN_Nod)
		{
			//m_pICAN_Nod->Out(&can_sMsgBroadCast);									// Update its part in other's PDO  throgh can bus
			m_pICAN_Nod->Out(&pCan_sMsgBroadCast);									// Update its part in other's PDO  throgh can bus
		}
	}
	bool CPedestrianLight::setget_PDO(tCAN& msg, bool set)
	{
		BYTE ndId = msg.data[0] & 0x0F;
		if (set)
		{
			// if the class object is to be syncronised  to msg, msg must be of wright type !
			if (!((msg.data[0] & 0xE0) == CMS_BROADCAST))				// 1110 0000 = 0xE0
				return false;										// wrong message type
			else
				for (int i = 0; i < 8; i++)
					m_PDO[ndId][i] = msg.data[i];
		}
		else
		{
			for (int i = 0; i < 8; i++)
				msg.data[i] = m_PDO[ndId][i];
		}
		return true;
	}
}	// namespace
